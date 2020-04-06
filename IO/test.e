use "cstd.e"
use "boost.e"
use "gl.e"

main()(
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
    int GL_Color_Buffer_Bit = 16384
    int GL_QUADS = 7

    while (a == 0)
    (
        push GL_Color_Buffer_Bit
        _glClear@4()
        push GL_QUADS
        _glBegin@4()           
            push 1.0
            push 0.0
            push 0.0
            _glColor3f@12()

            push (-0.5)
            push (-0.5)
            (_glVertex2f@8())

            push 0.5
            push (-0.5)
            (_glVertex2f@8())

            push 0.5
            push 0.5
           (_glVertex2f@8())

            push (-0.5)
            push 0.5
            (_glVertex2f@8())
        _glEnd@0()

        _glfwSwapBuffers(window)


        _glfwPollEvents()

        a = _glfwWindowShouldClose(window)
    )

    _glfwTerminate()
    return 0
)