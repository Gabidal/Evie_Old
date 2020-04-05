use "cstd.e"
use "boost.e"
use "gl.e"

main()(
    int window = 0
    int Title = 0
    short tail = 0

    int f1 = _glfwInit()
    if (f1 != 1)(
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

    while (a < 1)
    (
        __imp__glClear@4(16384)

        _glfwSwapBuffers(window)

        _glfwPollEvents()
    )

    _glfwTerminate()
    return 0
)