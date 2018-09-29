#include "Shader.hpp"
#include "Program.hpp"
#include "Vec4.hpp"
#include "Camera.hpp"
#include "Mat4.hpp"
#include "Debug.hpp"

#include <iostream>
#include <cmath>
#include <GL/freeglut.h>


const unsigned int windowWidth = 600, windowHeight = 600;

// 2D camera
static GLngin::Camera camera;


static std::unique_ptr<GLngin::Program> program (new GLngin::Program);

class Triangle {
	unsigned int vao;	// vertex array object id
	float sx, sy;		// scaling
	float wTx, wTy;		// translation
public:
	Triangle () {
		Animate (0);
	}

	void Create () {
		glGenVertexArrays (1, &vao);	// create 1 vertex array object
		glBindVertexArray (vao);		// make it active

		unsigned int vbo[2];		// vertex buffer objects
        glGenBuffers (2, vbo);	// Generate 2 vertex buffer objects

		// vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
		glBindBuffer (GL_ARRAY_BUFFER, vbo[0]); // make it active, it is an array
		float vertexCoords[] = { -8, -8,  -6, 10,   8, -2 };	// vertex data on the CPU
		glBufferData (GL_ARRAY_BUFFER,      // copy to the GPU
			         sizeof (vertexCoords), // number of the vbo in bytes
					 vertexCoords,		   // address of the data array on the CPU
					 GL_STATIC_DRAW);	   // copy to that part of the memory which is not modified 
		// Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
		glEnableVertexAttribArray (0);
		// Data organization of Attribute Array 0 
		glVertexAttribPointer (0,			// Attribute Array 0
			                  2, GL_FLOAT,  // components/attribute, component type
							  GL_FALSE,		// not in fixed point format, do not normalized
                              0, nullptr);     // stride and offset: it is tightly packed

		// vertex colors: vbo[1] -> Attrib Array 1 -> vertexColor of the vertex shader
		glBindBuffer (GL_ARRAY_BUFFER, vbo[1]); // make it active, it is an array
        static float vertexColors[] = { 1, 0, 0,  1, 1, 1,  0, 1, 0 };	// vertex data on the CPU
		glBufferData (GL_ARRAY_BUFFER, sizeof (vertexColors), vertexColors, GL_STATIC_DRAW);	// copy to the GPU

		// Map Attribute Array 1 to the current bound vertex buffer (vbo[1])
		glEnableVertexAttribArray (1);  // Vertex position
		// Data organization of Attribute Array 1
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Attribute Array 1, components/attribute, component type, normalize?, tightly packed
	}

	void Animate (float t) {
		sx =  sinf (t);
		sy =  cosf (t);
		wTx = 4 * cosf (t / 2);
		wTy = 4 * sinf (t / 2);
	}

	void Draw () {
        GLngin::Math::Mat4 Mscale (sx, 0, 0, 0,
			        0, sy, 0, 0,
			        0, 0, 0, 0,
			        0, 0, 0, 1); // model matrix

        GLngin::Math::Mat4 Mtranslate (1,   0,  0, 0,
			            0,   1,  0, 0,
                        0,   0,  1, 0,
			          wTx, wTy,  0, 1); // model matrix

        GLngin::Math::Mat4 MVPTransform = Mscale * Mtranslate * camera.V () * camera.P ();

		// set GPU uniform matrix variable MVP with the content of CPU variable MVPTransform
        if (!program->SetUniformMat4 ("MVP", MVPTransform))
            printf ("uniform MVP cannot be set\n");

		glBindVertexArray (vao);	// make the vao and its vbos active playing the role of the data source
		glDrawArrays (GL_TRIANGLES, 0, 3);	// draw a single triangle with vertices defined in vao
        glBindVertexArray (0);
	}
};

class LineStrip {
    GLuint vao, vbo;        // vertex array object, vertex buffer object
    float  vertexData[100]; // interleaved data of coordinates and colors
    unsigned char    nVertices;       // number of vertices
public:
    LineStrip () {
        nVertices = 0;
    }
    void Create () {
        glGenVertexArrays (1, &vao);
        glBindVertexArray (vao);

        glGenBuffers (1, &vbo); // Generate 1 vertex buffer object
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        // Enable the vertex attribute arrays
        glEnableVertexAttribArray (0);  // attribute array 0
        glEnableVertexAttribArray (1);  // attribute array 1
        // Map attribute array 0 to the vertex data of the interleaved vbo
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), reinterpret_cast<void*> (0)); // attribute array, components/attribute, component type, normalize?, stride, offset
        // Map attribute array 1 to the color data of the interleaved vbo
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), reinterpret_cast<void*> (2 * sizeof (float)));
    }

    void AddPoint (float cX, float cY) {
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        if (nVertices >= 20) return;

        GLngin::Math::Vec4 wVertex = GLngin::Math::Vec4 (cX, cY, 0, 1) * camera.Pinv () * camera.Vinv ();
        // fill interleaved data
        vertexData[5 * nVertices]     = wVertex[0];
        vertexData[5 * nVertices + 1] = wVertex[1];
        vertexData[5 * nVertices + 2] = 1; // red
        vertexData[5 * nVertices + 3] = 1; // green
        vertexData[5 * nVertices + 4] = 0; // blue
        nVertices++;
        // copy data to the GPU
        glBufferData (GL_ARRAY_BUFFER, nVertices * 5U * sizeof (float), vertexData, GL_DYNAMIC_DRAW);
    }

    void Draw () {
        if (nVertices > 0) {
            GLngin::Math::Mat4 VPTransform = camera.V () * camera.P ();

            if (!program->SetUniformMat4 ("MVP", VPTransform))
                printf ("uniform MVP cannot be set\n");

            glBindVertexArray (vao);
            glDrawArrays (GL_LINE_STRIP, 0, nVertices);
            glBindVertexArray (0);
        }
    }
};

// The virtual world: collection of objects
static Triangle triangle;
static LineStrip lineStrip;

// Initialization, create an OpenGL context
static void onInitialization () {
	glViewport (0, 0, windowWidth, windowHeight);

    triangle.Create ();

    std::shared_ptr<GLngin::Shader> pVs (new GLngin::Shader (GL_VERTEX_SHADER));
    std::shared_ptr<GLngin::Shader> pFs (new GLngin::Shader (GL_FRAGMENT_SHADER));

    pVs->Init ("/home/lui/dev/cpp/gfx/Modules/a/shaders/a.vert");
    pFs->Init ("/home/lui/dev/cpp/gfx/Modules/a/shaders/a.frag");

    program->Init (pVs, nullptr, pFs, nullptr);

    // before linking we bind vertex shader attributes and fragment shader outputs
    GL_CALL (glBindFragDataLocation (program->GetHandle (), 0, "fragmentColor"));

    program->Link ();
	program->Enable ();
}

static void onExit () {
    program->Disable ();
	program.reset ();
	printf ("exit");
}

// Window has become invalid: Redraw
static void onDisplay () {
	glClearColor (0, 0, 0, 0);							// background color 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	triangle.Draw ();
    lineStrip.Draw ();
	glutSwapBuffers ();									// exchange the two buffers
}

// Key of ASCII code pressed
static void onKeyboard (unsigned char key, int /*pX*/, int /*pY*/) {
	switch (key) {
        case 27: exit (0);
        default: break;
	}
}

// Key of ASCII code released
static void onKeyboardUp (unsigned char /*key*/, int /*pX*/, int /*pY*/) {

}

// Mouse click event
static void onMouse (int button, int state, int pX, int pY) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON and GLUT_DOWN / GLUT_UP
		float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
		float cY = 1.0f - 2.0f * pY / windowHeight;
		lineStrip.AddPoint (cX, cY);
		glutPostRedisplay ();     // redraw
	}
}

// Move mouse with key pressed
static void onMouseMotion (int /*pX*/, int /*pY*/) {
}

// Idle event indicating that some time elapsed: do animation here
static void onIdle () {
	long time = glutGet (GLUT_ELAPSED_TIME); // elapsed time since the start of the program
    float sec = time * 1e-3f;				// convert msec to sec
	camera.Animate (sec);					// animate the camera
	triangle.Animate (sec);					// animate the triangle object
	glutPostRedisplay ();					// redraw the scene
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Do not touch the code below this line

int main (int argc, char * argv[]) {
	glutInit (&argc, argv);
#if !defined (__APPLE__)
    glutInitContextVersion (3, 3);
#endif
	glutInitWindowSize (windowWidth, windowHeight);				// Application window is initially of resolution 600x600
	glutInitWindowPosition (100, 100);							// Relative location of the application window
#if defined (__APPLE__)
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_3_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
	glutCreateWindow (argv[0]);

#if !defined (__APPLE__)
	glewExperimental = true;	// magic
	glewInit ();
#endif

    std::cout << GLngin::GetGLInfoString () << std::endl;

	onInitialization ();

	glutDisplayFunc (onDisplay);                // Register event handlers
	glutMouseFunc (onMouse);
	glutIdleFunc (onIdle);
	glutKeyboardFunc (onKeyboard);
	glutKeyboardUpFunc (onKeyboardUp);
	glutMotionFunc (onMouseMotion);

	glutMainLoop ();
	onExit ();
    return 0;
}
