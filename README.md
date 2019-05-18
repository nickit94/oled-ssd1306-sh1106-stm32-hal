# oled-ssd1306-sh1106-stm32-hal
Драйвер OLED дисплеев на чипах SSD1306 или SH1106 для STM32 на HAL с русскими и английскими шрифтами.

## Описание
Проект с драйвером для OLED дисплея SSD1306 или SH1106 (китайский клон SSD1306 только с постраничным выводом), подключаемый по интерфейсу I2C. Разработан в SW4STM32 + CubeMX.

В комплекте набор русских и английских шрифтов разных размеров и шрифт больших цифр. 
Чтобы была возможность выводить русский текст на экран, необходимо набирать русский текст, но на английской раскладке. Пример в конце. 
Используется буфер. 
Реализован только постраничный способ выгрузки буфера в память дисплея для совместимости с популярным клоном SH1106. 

#### Проект собран в CubeMX 5.1.0 для чипа STM32F103C8Tx со следуюшими настройками: 
* System Core -> RCC -> High Speed Clock = Crystal
* System Core -> Sys -> Debug = Serial Wire
* Connectivity -> I2C1 -> I2C = I2C
* В Parameter Settings -> I2C Speed Mode = Fast Mode (иначе слишком медленно обновляется дисплей при анимациях)
* Частота установлена максимальная - 72 MHz

#### HAL
Сам драйвер стыкуется с HAL только в двух местах - в функции `OLED_SendCommand()` и функции `OLED_SendData()`, соответственно, драйвер можно привязать к любой платформе, реализовав лишь функцию отправки по протоколу I2C.


## Установка
Установка не требуется. Достаточно просто скачать весь проект и скопировать папку STM32_OLED в workspase SW4STM32, после чего открыть его через IDE и пользоваться. 

Вариант второй: создать проект под свой микроконтроллер STM32 в CubeMX, настроив так, как описано выше, после чего скопировать файлы `OLED.c`, `OLED_Fonts.c`, `OLED_Icons.c` из папки `STM32_OLED\Src` в папку `Src` нового проекта и скопировать файлы `OLED.h`,  `OLED_Fonts.h`, `OLED_Icons.h` из папки `STM32_OLED\Inc` в папку `Inc` нового проекта. 



## Основные функции

* `OLED_GetWidthStr(const char* str)` - Получить ширину строки в пикселях. Удобно для выравнивания текста

* `OLED_Invert(uint8_t inverted)`- Инвертировать дисплей

* `OLED_SetContrast(uint8_t contrast)` Изменить яркость дисплея

* `OLED_DrawNum(int16_t num, uint8_t x, uint8_t y, uint8_t mode)` - Напечатать число

* `OLED_DrawStr(const char *str, uint8_t x, uint8_t y, uint8_t mode)` - Напечатать строку

* `OLED_DrawBitmap(const uint8_t *progmem_bitmap, uint8_t height, uint8_t width, uint8_t pos_x, uint8_t pos_y)` - Вывод иконки в формате Bitmap

* `OLED_DrawXBM(int16_t xMove, int16_t yMove,  const uint8_t *xbm)` - Вывод иконки в формате XBM

* `OLED_DrawBuffer(const uint8_t *progmem_buffer)` - Вывод заранее подготовленного буфера

* `OLED_DrawVLine(uint8_t x, uint8_t y, uint8_t length)` - Нарисовать вертикальную линию

* `OLED_DrawHLine(uint8_t x, uint8_t y, uint8_t length, uint8_t mode)` - Нарисовать горизонтальную линию

* `OLED_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)` - Нарисовать прямоугольник

* `OLED_DrawRectangleFill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)` - Нарисовать закрашенный прямоугольник

* `OLED_DrawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3)` - Нарисовать треугольник

* `OLED_DrawTriangleFill(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3)` - Нарисовать закрашенный треугольник

* `OLED_DrawCircle(int16_t x0, int16_t y0, uint8_t r)` - Нарисовать круг

* `OLED_DrawCircleFill(int16_t x0, int16_t y0, int16_t radius)` - Нарисовать закрашенный круг

* `OLED_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)` - Нарисовать произвольную линию

* `OLED_UpdateScreen()` - Обновить весь дисплей разом

* `OLED_UpdateOnePage(uint8_t page_number)` - Обновить одну из 8 страниц. Удобно, если меняется незначительная часть дисплея или если использовать в фоне, обновляя по одной странице при каждом вызове - повышается быстродействие



## Пример использования

```c
  /* Init OLED */
  OLED_Init(&hi2c1);

  /* Text */
  FontSet(Segoe_UI_Rus_12);
  OLED_DrawStr("Ghbdtn vbh!", 0, 15, 1);		// "Привет мир!"
  FontSet(Segoe_UI_Eng_10);
  OLED_DrawStr("by nickit94", RIGHT, 48, 1);

  /* Icon */
  OLED_DrawXBM(100, 10, icon_clock);

  /* Figures */
  OLED_DrawRectangle(11, 10, 88, 35);
  OLED_DrawCircle(10, 60, 3);
  OLED_DrawCircleFill(18, 60, 3);
  OLED_DrawCircle(26, 60, 3);
  OLED_DrawTriangle(40, 63, 45, 53, 50, 63);
  OLED_DrawTriangleFill(47, 53, 52, 63, 57, 53);

  /* Update screen */
  OLED_UpdateScreen();
```

#### В результате на дисплее должно получиться следующее:
![Результат успешной работы примера](https://github.com/nickit94/oled-ssd1306-sh1106-stm32-hal/blob/master/ResultExample.jpg)
