#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup(void)
{
  /* 允许 GPIOB 时钟. */
  /* 手动: */
  // RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
  /* 使用库函数: */
  rcc_periph_clock_enable(RCC_GPIOB);

  /* 设置 GPIO1 (端口B) 推挽输模式. */
  /* 手动y: */
  // GPIOB_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((12 - 8) * 4) + 2));
  // GPIOB_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((12 - 8) * 4));
  /* 使用库函数: */
  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
          GPIO_CNF_OUTPUT_PUSHPULL, GPIO1);
}

int main(void)
{
  int i;

  gpio_setup();

  /* i使 LED (PB1) 闪烁. */
  while (1) {
    /* 手动: */
    // GPIOC_BSRR = GPIO12;    /* LED off */
    // for (i = 0; i < 800000; i++)  /* Wait a bit. */
    //   __asm__("nop");
    // GPIOC_BRR = GPIO12;    /* LED on */
    // for (i = 0; i < 800000; i++)  /* Wait a bit. */
    //   __asm__("nop");

    /* 使用库函数 gpio_set()/gpio_clear(): */
    // gpio_set(GPIOC, GPIO12);  /* LED off */
    // for (i = 0; i < 800000; i++)  /* Wait a bit. */
    //   __asm__("nop");
    // gpio_clear(GPIOC, GPIO12);  /* LED on */
    // for (i = 0; i < 800000; i++)  /* Wait a bit. */
    //   __asm__("nop");

    /* 使用库函数 gpio_toggle(): */
    gpio_toggle(GPIOB, GPIO1);  /* LED on/off */
    for (i = 0; i < 800000; i++)  /* Wait a bit. */
      __asm__("nop");
  }

  return 0;
}
