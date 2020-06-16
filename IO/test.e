use "cstd.e"
use "boost.e"
use "glfw3.lib"
use "OpenGL32.Lib"

int GL_Color_Buffer_Bit = 16384
int GL_QUADS = 7

main()(

    int ptr window = 0
    char ptr Title = 0
    short tail = 0

    if (_glfwInit() != 1)(
        return (-1)
    )

    window = (_glfwCreateWindow(640, 480, @Title, 0, 0))
    if (window == 0)
    (
        _glfwTerminate()
        return (-1)
    )
    _glfwMakeContextCurrent(window)

    int a = 0

    while (a == 0)
    (
        #glClearColor(1.0, 0.0, 1.0, 1.0)
        _glClear(GL_Color_Buffer_Bit)
        _glBegin(GL_QUADS)
            _glColor3f(1.0, 0.0, 0.0)
            _glVertex2f((-0.5), (-0.5))
            _glVertex2f(0.5, (-0.5))
            _glVertex2f(0.5, 0.5)
            _glVertex2f((-0.5), 0.5)
        _glEnd()

        _glFlush()

        _glfwSwapBuffers(window)


        _glfwPollEvents()

        a = _glfwWindowShouldClose(window)
    )

    _glfwTerminate()
    return 0
)