#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

static void clock_setup(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  rcc_periph_clock_enable(RCC_GPIOB);
}

static void gpio_setup(void)
{
  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO1);
}

static void systick_setup(void)
{
  /* 72MHz / 8 => 9000000 counts per second */
  systick_counter_disable();
  systick_interrupt_disable();
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(9000 * 1000);
  systick_counter_enable();
}

int main(void)
{
  clock_setup();
  gpio_setup();
  systick_setup();

  while(1)
  {
    if(systick_get_countflag())
    {
      gpio_toggle(GPIOB, GPIO1);
    }
  }

  return 0;
}
