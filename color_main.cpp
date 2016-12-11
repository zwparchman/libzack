#include "color.h"
#include <stdio.h>


int main(){
    printf("visual test\n");

    printf("%sblack background\n" , black_background);
    printf("%sred background\n", red_background);
    printf("%sgreen background\n", green_background);
    printf("%syellow background\n", yellow_background);
    printf("%sblue background\n", blue_background);
    printf("%smagenta background\n", magenta_background);
    printf("%scyan background\n", cyan_background);
    printf("%swhite background\n", white_background);
    printf("%safter reset\n", off_attr);

    printf("%sblack forground\n" , black_forground);
    printf("%sred forground\n", red_forground);
    printf("%sgreen forground\n", green_forground);
    printf("%syellow forground\n", yellow_forground);
    printf("%sblue forground\n", blue_forground);
    printf("%smagenta forground\n", magenta_forground);
    printf("%scyan forground\n", cyan_forground);
    printf("%swhite forground\n", white_forground);
    printf("%safter reset\n", off_attr);


    printf("%sreverse_video_attr%s\n", reverse_video_attr, off_attr);
    printf("%sbold_attr%s\n", bold_attr, off_attr);
    printf("%sunderscore_attr%s\n", underscore_attr, off_attr);
    printf("%sconcealed_attr%s\n", concealed_attr, off_attr  );
    printf("%sblink_attr%s\n", blink_attr, off_attr  );

    printf("%sgreen on black%s\n", GREEN_FORGROUND BLACK_BACKGROUND, off_attr);
    printf("%sblack on green%s\n", BLACK_FORGROUND GREEN_BACKGROUND, off_attr);

    printf("%sSmart green on black%s\n", smart_color_print(GREEN_FORGROUND BLACK_BACKGROUND), off_attr);


    printf("%safter reset\n", off_attr);
}
