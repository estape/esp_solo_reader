#include "SensorDriver.h"
#include <iostream>
#include "regex.h"
#include "esp_log.h"
#include "string.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "SensorReader.h"

gpio_config_t sensor_io_conf;

void InitSensorReader()
{
    // Inicializa o sensor
    sensor_io_conf.pin_bit_mask = 1ULL << GPIO_NUM_35;
    sensor_io_conf.intr_type = GPIO_INTR_DISABLE;
    sensor_io_conf.mode = GPIO_MODE_INPUT;
    sensor_io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    sensor_io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&sensor_io_conf);
}

/**
 * @brief Simula a leitura de um valor do sensor e o retorna como uma string.
 *
 * @return std::string O valor simulado do sensor.
 */
std::string ReadSensorValue()
{
    // Simula a leitura do sensor
    return "312";
}

/**
 * @brief Verifica os valores do sensor SoloReader.
 *
 * Este método inicializa o leitor de sensores, verifica se o valor lido do sensor
 * corresponde a um padrão esperado (usando regex) e, se válido, converte o valor
 * para um inteiro e o retorna. Caso o valor não seja válido, retorna -1.
 *
 * @return int O valor do solo lido do sensor, ou -1 se o valor for inválido.
 */
int SensorReader::CheckSoloReaderValues()
{
    SensorDriver refSensorDriver;

    bool sensorIsValid = false;
    int soilValue = 0;

    InitSensorReader();

    while (1)
    {
        if (refSensorDriver.CheckRegex(ReadSensorValue()))
        {
            soilValue = std::stoi(ReadSensorValue());
            return soilValue;
        }
        else
        {
            return -1;
        }
    }
}