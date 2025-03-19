#include <iostream>
#include "regex.h" // Biblioteca para expressões regulares do ESP-IDF (ESP 32)
#include "esp_log.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void MoistureDevice()
{
    int moistureValue = 0; // Simulated value, replace with actual sensor reading
    ParseRegex(moistureValue);
}

/**
 * @brief Analisa um valor de umidade usando uma expressão regular para validar seu formato.
 *
 * Esta função compila uma expressão regular para validar se o valor de umidade fornecido
 * é uma string numérica com até 4 dígitos. Se a expressão regular falhar ao compilar,
 * uma mensagem de erro será registrada. Se a validação falhar, outra mensagem de erro será registrada.
 *
 * Após a compilação e validação da expressão regular, é verificado que o valor da umidade está fora de seu formato esperado caso haja anormalidade de sinal do sensor (de 1 a 4 digitos).
 *
 * @param moistureValue O valor de umidade a ser validado.
 * @return std::string Retorna uma string vazia. (Nota: A função atualmente não retorna nenhum resultado significativo.)
 */
std::string ParseRegex(int moistureValue)
{
    regex_t refRegex; // Reference regex

    std::string moistureResult = "";
    int reti = regcomp(&refRegex, "^\\d{0,4}$", 0); // Compila a expressão regular para validar se o valor de umidade é de até 4 dígitos

    if (reti != 0)
    {
        ESP_LOGE("REGEX", "Erro ao compilar a expressão regular");
    }

    else
    {
        regexec(&refRegex, std::to_string(moistureValue).c_str(), 0, NULL, 0); // Verifica se o valor de umidade é um número de 1 a 4 dígitos
        regfree(&refRegex);

        if (reti == 0)
        {
            // enviar para IA
        }
        else
        {
            ESP_LOGE("Sensor", "Erro ao ler o sensor de umidade"); // Possivel anormalia de sinal do sensor
        }
    }
}

/**
 * @brief Função principal do programa.
 * 
 * Esta função é a função principal do programa. Ela chama a função MoistureDevice() que simula a leitura de um sensor de umidade.
 */
extern "C" void app_main(void)
{
    MoistureDevice();
}
