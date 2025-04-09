#include <iostream>
#include "regex.h"
#include "esp_log.h"
#include "string.h"
#include "SensorDriver.h"


/**
 * @brief Verifica se o valor de umidade fornecido está em um formato válido e dentro do intervalo esperado.
 * 
 * Esta função utiliza expressões regulares para validar se a string fornecida representa
 * um número inteiro de 1 a 4 dígitos. Caso o valor seja válido, ele é convertido para um inteiro
 * e verificado se está no intervalo de 0 a 1023. Logs são gerados para indicar o sucesso ou falha
 * da validação.
 * 
 * @param moistureValue Uma string representando o valor de umidade a ser validado.
 *                      Deve conter apenas números de 1 a 4 dígitos.
 * 
 * @return TRUE = Se o valor estiver no formato correto e dentro do intervalo permitido (0 a 1023) ou FALSE = Se o valor estiver em um formato inválido ou fora do intervalo permitido.
 * 
 * @note Em caso de erro na compilação da expressão regular, a função retorna false e registra um log de erro.
 * 
 * @warning Certifique-se de que a string fornecida contenha somente caracteres numéricos,
 *          pois caso a contrário resultará em falha na validação.
 */
bool SensorDriver::CheckRegex(std::string moistureValue)
{
    int moistureResult = 0;
    regex_t refRegex;

    // Compilando regex simples para validar 1 a 4 dígitos
    int reti = regcomp(&refRegex, "^[0-9]\\{1,4\\}$", REG_BASIC);

    if (reti != 0)
    {
        ESP_LOGE("REGEX", "Erro ao compilar a expressão regular");
        return false;
    }

    // Validando se a string é um número de 1 a 4 dígitos
    reti = regexec(&refRegex, moistureValue.c_str(), 0, NULL, 0);
    regfree(&refRegex);

    if (reti == 0)
    {
        moistureResult = std::stoi(moistureValue);

        if (moistureResult >= 0 && moistureResult <= 1023)
        {
            return true;
        }
            
        else
        {
            ESP_LOGE("Sensor", "Erro ao ler o sensor de umidade - Valor fora do intervalo. (1023 - 0).");
            return false;
        }
    }
    else
    {
        ESP_LOGE("Sensor", "Erro ao ler o sensor de umidade - Formato inválido. Código: %d", reti);
        return false;
    }
}

/**
 * @brief Determina o nível de umidade do solo com base no valor lido do sensor,
 * caso o valor esteja fora do intervalo esperado, será registrado um erro no log.
 * @param moistureValue Valor de umidade lido pelo sensor (intervalo esperado: 1023 (super seco) a 0 (encharcado)).
 * 
 * @return Nível de umidade do solo em inteiro.
 * @note 3 = Encharcado (valores entre 0 e 255)
 * @note 2 = Úmido (valores entre 256 e 511)
 * @note 1 = Seco (valores entre 512 e 767)
 * @note 0 = Super seco (valores entre 768 e 1023)
 * @note -1 = Erro (valor fora do intervalo esperado)
 */
int SensorDriver::GetMoistureLevel(int moistureValue)
{
    switch (moistureValue)
    {
        case 0 ... 255:
            return 3; // Encharcado
        case 256 ... 511:
            return 2; // Úmido
        case 512 ... 767:
            return 1; // Seco
        case 768 ... 1023:
            return 0; // Super seco
        default:
            ESP_LOGE("Sensor", "Erro ao determinar a leitura do solo.");
            return -1; // Erro
    }
}