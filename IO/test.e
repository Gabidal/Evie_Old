use "cstd.e"
use "boost.e"
use "gl.e"

main()(


    int GL_Color_Buffer_Bit = 16384
    int GL_QUADS = 7

    int window = 0
    int Title = 0
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
        (glClear(GL_Color_Buffer_Bit))
        (glBegin(GL_QUADS))
            (glColor3f(1.0, 0.0, 0.0))
            (glVertex2f((-0.5), (-0.5)))
            (glVertex2f(0.5, (-0.5)))
            (glVertex2f(0.5, 0.5))
            (glVertex2f((-0.5), 0.5))
        (glEnd())

        (glFlush())

        _glfwSwapBuffers(window)


        _glfwPollEvents()

        a = _glfwWindowShouldClose(window)
    )

    _glfwTerminate()
    return 0
)