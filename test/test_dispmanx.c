#include <rpigrafx.h>
#include <stdio.h>

int main()
{
    int width, height;

    rpigrafx_get_screen_size(&width, &height);
    printf("The screen size is %dx%d\n", width, height);

    return 0;
}
