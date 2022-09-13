#include "bu_conf.h"

int main(){
	int integer = 0;
	float floating = 0.0f;
	
	uint8_t rgb_color[3] = {0};
	uint8_t rgba_color[4] = {0};

	int unset = 64;
	buc_option* conf = create_conf();

	
	add_option( conf, "integer_option", BUC_INT, &integer);
	add_option( conf, "floating_option", BUC_FLOAT, &floating);
	add_option( conf, "rgb_color", BUC_RGB, &rgb_color);
	add_option( conf, "rgba_color", BUC_RGBA, &rgba_color);
	add_option( conf, "unset_in_config", BUC_INT, &unset);

	printf("\nInitial values:\n\n");
	
	printf("integer_option is\t %d\n", integer);
	printf("floating_option is\t %f\n", floating);
	printf("rgb_color option is:\t %hhu, %hhu, %hhu \n", rgb_color[0], rgb_color[1], rgb_color[2]);	
	printf("rgba_color option is:\t %hhu, %hhu, %hhu, %hhu \n", rgba_color[0], rgba_color[1], rgba_color[2], rgba_color[3]);
	printf("unset_in_config is\t %d\n", unset);

	load_conf("example_config.conf", conf);
	
	printf("\nInitial values:\n\n");
	
	printf("integer_option is\t %d\n", integer);
	printf("floating_option is\t %f\n", floating);
	printf("rgb_color option is:\t %hhu, %hhu, %hhu \n", rgb_color[0], rgb_color[1], rgb_color[2]);	
	printf("rgba_color option is:\t %hhu, %hhu, %hhu, %hhu \n", rgba_color[0], rgba_color[1], rgba_color[2], rgba_color[3]);
	printf("unset_in_config is\t %d\n", unset);
	
}

