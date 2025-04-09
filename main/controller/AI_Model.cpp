#include "AI_Model.h"
#include "SensorDriver.h"
#include <iostream>
#include <string>
#include <vector>
#include "esp_log.h"

std::vector<int> humidityData;
std::vector<int> temperatureData;

/**
 * @brief Adiciona dados de umidade e temperatura ao modelo de IA.
 * @param humidity Nível de umidade do solo (1023 a 0).
 * @param temperature Temperatura ambiente (em graus Celsius).
 */
void AI_Model::addData(int humidity, int temperature)
{
    if (humidityData.size() > 10)
        humidityData.erase(humidityData.begin());
    if (temperatureData.size() > 10)
        temperatureData.erase(temperatureData.begin());

    humidityData.push_back(humidity);
    temperatureData.push_back(temperature);
}

// Toma decisãos com base nos dados de umidade e temperatura
std::string AI_Model::makeDecision()
{
    if (humidityData.empty())
        return "Sem dados suficientes.";

    int currentHumidity = humidityData.back();
    int currentTemperature = temperatureData.back();

    if (currentHumidity < 30 && currentTemperature > 30)
    {
        return "Alerta: Solo seco e temperatura alta! Recomenda-se irrigação. Sugestão: Regar";
    }
    else if (currentHumidity > 80)
    {
        return "Aviso: Solo encharcado! Evite irrigação. Sugestão: Não Regar";
    }
    else
    {
        return "Condição normal. Monitorando...";
    }
}