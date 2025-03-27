#include <iostream>
#include "SensorDriver.h"
#include "ConsoleScreen.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"

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
    printf("\033[44;97m"); // ANSI escape code para mudar a cor de fundo do console.
}

void ConsoleScreen::MoistureSensorView(int moistureLevel)
{
    SensorDriver refSensorDriver;
    int soilMoistureLvl = -2;

    esp_log_level_set("gpio", ESP_LOG_WARN);

    ChangeColor();
    ClearConsole();

    std::cout << "=============================\n";
    std::cout << "|     SENSOR DE UMIDADE     |\n";
    std::cout << "=============================\n\n";

    soilMoistureLvl = refSensorDriver.GetMoistureLevel(moistureLevel);

    printf("Nível de umidade detectado pelo sensor: %d (0 = seco, 1 = úmido, 2 = encharcado)\n\n", soilMoistureLvl);
    printf("Aplicação: Monitoramento de umidade do solo para agricultura.\n\n");

    switch (soilMoistureLvl)
    {
    case 0:
        printf("Resultado:\nSolo seco. Recomendação: Regue o solo imediatamente para evitar danos às plantas e garantir o crescimento saudável.\n");
        break;
    case 1:
        printf("Resultado:\nSolo úmido. Recomendação: O solo está em boas condições para o cultivo, não é necessário regar agora.\n");
        break;
    case 2:
        printf("Resultado:\nSolo encharcado. Recomendação: Evite regar o solo para prevenir o apodrecimento das raízes e possíveis perdas na colheita.\n");
        break;
    default:
        printf("Resultado:\nErro ao ler o sensor de umidade. Recomendação: Verifique o sensor e tente novamente para garantir leituras precisas.\n");
        break;
    }
}