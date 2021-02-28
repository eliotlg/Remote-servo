#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gpiod.h>
#include <stdbool.h>

int main(int ac, char **av)
{
  struct gpiod_chip *chip = gpiod_chip_open_by_name("gpiochip0");
  struct gpiod_line *line = gpiod_chip_get_line(chip, 17);
  int ret = gpiod_line_request_output(line, "Consumer", 0);
  fprintf(stdout, "Enter cyclic\n", ret);
  char buffer[80];
  int cyclic;

  scanf("%[^\n]", buffer);
  fgetc(stdin);
  fprintf(stdout, "Thanks!\n");
  cyclic = atoi(buffer);

  ret = gpiod_line_set_value(line, false);

  int implicit_cyclic = 1000000/50;
  int implicit_cyclic_on = (implicit_cyclic * cyclic) / 100;
  int implicit_cyclic_off = implicit_cyclic - implicit_cyclic_on;

  fprintf(stdout, "Starting motor control with a cyclic of %d\n", cyclic);
  while (true) {
    ret = gpiod_line_set_value(line, true);
    //    fprintf(stdout, "%d\n", ret);
    usleep(implicit_cyclic_on);
    ret = gpiod_line_set_value(line, false);
    //    fprintf(stdout, "%d\n", ret);
    usleep(implicit_cyclic_off);
  }
  return (0);
}
