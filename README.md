# Simulador de *assembler*

## Introdução
Repositório para armazenamento dos documentos do projeto de simulador de *assembler*.  
O simulador de *assembler* é um projeto desenvolvido no contexto na disciplina de [Arquitetura de Computadores](https://github.com/claytonjasilva/claytonjasilva.github.io/blob/main/arq_aulas.md), turmas 2023.2,
com o objetivo de sedimentar os conceitos adquiridos na disciplina.  
O projeto consiste em uma máquina digital baseada na plataforma do Arduíno Atmega 2560.  
Permite a prática de vários tópicos dos cursos para os quais a disciplina é ministrada com destaque aos seguintes:  
1. Programação em C/C++
2. Projetos sistemas baseados em modelos ágeis
3. Sistemas digitais embarcados
4. Microcontroladores
5. Programação em linguagem de montagem (*assembly*).

## Especificações
Sistema baseado no microcontrolador Atmel ATmega V2560, Arduíno Mega 2560 com shield baseado no LCD 1602.  
Na versão atual, o sistema recebe do usuário, através do monitor serial, instruções em sequência, cujas palavras pertencem a código binário de 11 bits
como entrada E(E10 E9 ... E0).  
A palavra binária de entrada se decompõe em opcode e operando.  
- Os três bits mais significativos da cada palavra do código representam o *opcode* das operações a realizar.
- Os oito bits menos signficativos constituem o campo de operando, cuja forma depende de cada operação. 

### Tabela de dados
| Opcode (E10 E9 E8) | Mnemônico | Significado |
| - | - | - |
| 000	| Comp1 |	Gera o complemento de 1 do operando E7 E6 ... E0 e carrega o resultado em uma variável X do sketch. |
| 001	| Add	| Soma os operandos (E7 E6 E5 E4) e (E3 E2 E1 E0) e carrega o resultado em uma variável X do sketch. |
| 010	| AddI	| Soma imediata do operando E7 E6 ... E0 com o conteúdo de uma variável X e devolve o resultado em X do sketch. |
| 011	| Sub	| Subtrai os operandos (E7 E6 E5 E4) e (E3 E2 E1 E0) e carrega o resultado em uma variável X do sketch. |
| 100	| SubI	| Subtração imediata do operando E7 E6 ... E0 com o conteúdo de uma variável X e devolve o resultado em X do sketch. |
| 101	| Ldo	| Lê o conteúdo da variável X, se operando é igual a 0, e da variável Y, se o operando é diferente de 0, ambas do sketch. Deve apresentar o conteúdo como saída no LCD 1602 em uma palavra binária de 9 bits, S(S8 S7 S6 S5 ... S0) representada em bit sinal. |
| 110	| Sto	| Armazena o operando E7 E6 ... E0 na variável X do sketch. |
| 111 |	Trans |	Copia o valor armazenado em uma variável X para uma variável Y, ambas do sketch. |



