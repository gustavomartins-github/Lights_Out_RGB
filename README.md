# LightsOut RGB

<p>
 O LightsOut RGB consiste em uma versão modificada do LightsOut, um jogo físico em que há uma matriz de luzes que podem estar ligadas ou desligadas (ON/OFF). Diante disso, o objetivo do jogo consiste em desligar todas as luzes, considerando que, ao clicar em determinado botão, o estado de sua luz e o estado das luzes adjacentes são invertidos. 
</p>
 Em contra partida, essa nova versão possui 4 estados possíveis (RED, GREEN, BLUE, OFF) abreviados, respectivamente, como (R, G, B, W). Somado a isso, a inversão de estado ocorre em todas as luzes vertical e horizontalmente ao botão clicado, com excessão de determinados botões "quebrados" que possuem comportamento específico. 
<p>

<p>
 Diante do exposto, o objetivo desse projeto consiste em criar um programa capaz de atender as seguintes demandas. São elas: 
</p>

<ol>
<li>ler a especificação do desafio (Input)</li>
<li>Gerar um modelo PDDL do jogo LightsOut RGB</li>
<li>Chamar um planejador</li>
<li>Obter o plano do planejador</li>
<li>Gerar a saída no formato especificado (Output)</li>
</ol>

<p>
 A seguir, confira as característica de cada tipo de botão, bem como as especificações de entrada e saída
</p>

# Botões 

 ID |                               Defeito                                |                 Mudança de Estado                | Representação |
----| -------------------------------------------------------------------- | ------------------------------------------------ | ------------- |
1   |                Não há mudança de estado quando clicado               | click em mesma linha ou coluna                   |       *       |
2   |    Não há mudança de estado decorrente de click em mesma coluna      | quando clicado ou click em mesma linha           |       _       |
3   |    Não há mudança de estado decorrente de click em mesma linha       | quando clicado ou click em mesma coluna          |       |       |
4   | Não há mudança de estado decorrente de click em mesma linha e coluna | quando clicado                                   |       #       |
5   |                                 Nenhum                               | quando clicado ou click em mesma linha ou coluna |       -       |

# Input

<p>
 O input deve ser lido pela entrada padrão e terminar em EOF, sendo formado por um conjunto de linhas que representarão uma matriz. Essa matriz representará o mapa do "jogo" e sua dimensão é implicita, sendo evidenciada conforme se faz a leitura das linhas. Por fim, cada linha consiste em uma string, onde cada caracter simboliza uma cor (R,G,B,W) ou tipo de botão (-, *, _, |, #).
 </p>

<p>
Ex.:<br>
Linha 1: *W-R-R-B <br>
Linha 2: -R|W-W-G <br>
Linha 3: -B-G_G-G <br>
Linha 4: -R-W-W#W <br>
</p>

# Output

<p>
 saída é composta por uma única linha contendo as coordenadas dos botões apertados, em ordem, a fim de obter todas as lâmpadas apagadas.
</p>

<br>

<p>
 Ex.: (click 2 3);(click 2 3);(click 0 0);(click 0 0);(click 0 0)
</p>

<i>Resumo (Mudança de Estados):</i>

 ID |       Defeito      |    quando clicado  | click em mesma linha | click em mesma coluna |
----| ------------------ | ------------------ | -------------------- | --------------------- |
1   | :white_check_mark: |        :x:         |  :white_check_mark:  |  :white_check_mark:   |
2   | :white_check_mark: |        :x:         |  :white_check_mark:  |          :x:          |
3   | :white_check_mark: |        :x:         |         :x:          |  :white_check_mark:   |
4   | :white_check_mark: | :white_check_mark: |         :x:          |          :x:          |
5   |        :x:         | :white_check_mark: |  :white_check_mark:  |  :white_check_mark:   |

# Tabela de comandos (C/C++)

Comando   | Função
--------- | ------
sudo apt-get install gcc | instalação do compilador .c
sudo apt-get install g++ | instalação do compilador .cc
gcc [file_name.c] -o[executable_name] | cria um executável a partir de um file.c
g++ [file_name.cc] -o[executable_name] | cria um executável a partir de um file.cc

# Referências

<ol>
<li><a href="https://www.brunoribas.com.br/flia/2024-1/">Fundamentos Lógicos da IA - 2024-1
UnB</a></li>
<li><a href="https://www.brunoribas.com.br/flia/2024-1/lightsoutrgb.html">LIGHTSOUT RGB* Apague todas as lâmpadas</a></li>
<ol>

