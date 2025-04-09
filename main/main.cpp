#include <iostream>
#include "SensorReader.h"
#include "ConsoleScreen.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

extern "C" void app_main(void) // Garante compatibilidade com C
{
    SensorReader refSensorReader;
    ConsoleScreen refConsoleScreen;

    int lastSoilMoisture = -1;

    while (1)
    {
        int soilMoisture = refSensorReader.CheckSoloReaderValues();

        if (soilMoisture >= 0)
        {
            if (soilMoisture != lastSoilMoisture)
            {
                refConsoleScreen.MoistureSensorView(soilMoisture);
                lastSoilMoisture = soilMoisture;
            }
        }
        else
        {
            ESP_LOGE("main", "Erro ao ler os valores do sensor de umidade.");
            std::cout << "Erro ao ler os valores do sensor de umidade." << std::endl;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}