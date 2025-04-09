#include <iostream>
#include "SensorDriver.h"
#include "ConsoleScreen.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "AI_Model.h"

/**
 * @brief Limpa o console e reposiciona o cursor no início.
 * 
 * Esta função utiliza códigos de escape ANSI para limpar o conteúdo
 * do console e reposicionar o cursor no canto superior esquerdo.
 * 
 * @note Certifique-se de que o terminal utilizado suporta códigos de escape ANSI.
 */
void ClearConsole()
{
    std::cout << "\033[2J\033[H"; // ANSI escape code para limpar o console e reposicionar o cursor no início.
}

/**
 * @brief Altera a cor de fundo do console para uma cor específica usando códigos de escape ANSI.
 *
 * Esta função utiliza o código de escape ANSI "\033[44;97m" para definir
 * a cor de fundo do console como azul (código 44) e a cor do texto como branco (código 97).
 *
 * @note Esta funcionalidade é compatível apenas com terminais que suportam códigos de escape ANSI.
 */
void ChangeColor()
{
    printf("\033[40;32m"); // ANSI escape code para mudar a cor de fundo do console.
}

/**
 * @brief Exibe informações sobre o nível de umidade do solo com base na leitura de um sensor.
 *
 * Esta função utiliza um driver de sensor para obter o nível de umidade do solo e exibe
 * recomendações baseadas no valor detectado. Os níveis de umidade são categorizados como:
 * 0 (seco), 1 (úmido) e 2 (encharcado). Caso ocorra um erro na leitura, uma mensagem de erro
 * será exibida.
 *
 * @param moistureLevel Valor bruto de entrada representando o nível de umidade do solo.
 *
 * @note A função também ajusta o nível de log do ESP para "WARN" para a tag "gpio".
 *       Certifique-se de que o driver do sensor está configurado corretamente para
 *       leituras precisas.
 */
void ConsoleScreen::MoistureSensorView(int moistureLevel)
{
    SensorDriver refSensorDriver;
    AI_Model refAIModel;

    /**
     * @brief Variável para armazenar o nível de umidade do solo.
     * @note 0 Seco
     * @note 1 Úmido
     * @note 2 Úmido
     * @note 3 Encharcado
     */
    int soilMoistureLvl = -1;
    std::string IADecision = "";
    std::string soilMoistureReturn = "";

    esp_log_level_set("gpio", ESP_LOG_WARN);

    ChangeColor();
    ClearConsole();

    std::cout << "=============================\n";
    std::cout << "|     SENSOR DE UMIDADE     |\n";
    std::cout << "=============================\n\n";

    printf("Aplicação: Monitoramento de umidade do solo para agricultura.\n\n");

    soilMoistureLvl = refSensorDriver.GetMoistureLevel(moistureLevel);
    refAIModel.addData(soilMoistureLvl, 0); // Adiciona dados de umidade e temperatura (0 como placeholder)
    IADecision = refAIModel.makeDecision(); // Faz uma decisão com base nos dados adicionados

    switch (soilMoistureLvl)
    {
        case 0:
            soilMoistureReturn = "Encharcado";
            break;
        case 1:
            soilMoistureReturn = "Úmido";
            break;
        case 2:
            soilMoistureReturn = "Seco";
            break;
        case 3:
            soilMoistureReturn = "Super seco";
            break;
        default:
            soilMoistureReturn = "Indefinido";
            break;
    }

    printf(IADecision.c_str());
    printf("\n\n=============================\n");
    std::cout << "Nível de umidade do solo: " << soilMoistureReturn << std::endl;
}