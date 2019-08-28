#include "../include/ship_generator.h"
#include "../include/board_generator.h"

/* SHIP GENERATOR */

namespace ShipG
{
    void Battleship(std::vector<std::vector<int>> &board, int col, int row)
    {
        std::random_device rand;   // Função geradora de valores randomicos
		std::mt19937 seed(rand()); // Função responsável por alterar a seed dos valores randomicos, para que sejam sempre diferentes

		std::uniform_int_distribution <> picker1(1, col - 1); // Função responsável por sortear um valor entre 0 e o número de colunas 
                                                          // Essa função irá escolher em qual coluna a "cabeça" do Battleship irá spawnar
		
		std::uniform_int_distribution <> picker2(1, row - 4); // Função responsável por definir em qual linha a "cabeça" do Battleship 										irá spawnar por meio de sorteio
                                                              /* O valor de row é decrescido de 3 pois caso a cabeça do battleship seja um 									valor maior que row-3,
                                                                 seu corpo irá sair do board, já que ele ocupa 4 espaços */
                                                              /* Dessa forma, o barco será colocado na posição vertical, já que cada parte do 									corpo subsequente irá
                                                                 spawnar na próxima linha abaixo */
        
        std::uniform_int_distribution <> picker3(1, col - 4); // Acrescento mais um picker para escolher uma coordenada no caso de colocar o 									barco na Horizontal.

        std::uniform_int_distribution <> V_or_H(0,1); // Define se o barco será spawnado na Vertical(0) ou na Horizontal(1).
		
        int shadow = 2;    // Valor para sobra do barco
        int guidance = V_or_H(seed); // Variável que recebe a orientação dos barcos (Vertical ou Horizontal).
     
        if(guidance == 0) // Orientação Vertical
        {
            // Variáveis responsáveis por definir a coordenada em que a "cabeça" do Battleship irá spawnar, baseado nos valores sorteados pelos pickers.
            auto posX = picker2(seed);
            auto posY = picker1(seed);

            for(int i(posX-1); i <= (posX+4); i++)
            {
                for (int j (posY-1); j <= (posY+1); j++)
                {
                    board[i][j] = shadow;
                }
            }
            
            for(int i(0); i < 4; i++)  // Spawna o Battleship no board na Vertical
            {
                board[posX+i][posY] = 1; 

            }
		//Colocando no arquivo
		std::ofstream myfile_2;
	       	myfile_2.open("the armada-format",std::ios_base::app);
	       	myfile_2 << "B" << " " << posX << " " << posY << " " << guidance << "\n";
	       	myfile_2.close();
        } 
        else // Orientação Horizontal
        {
            auto posX = picker1(seed);
            auto posY = picker3(seed);

            // Coloca as sombras do barco no mapa
            for(int i(posX-1); i <= (posX+1); i++)
            {
                for (int j (posY-1); j <= (posY+4); j++)
                {
                    board[i][j] = shadow;
                }
            }

            //Coloca o barco no mapa
            for(int i(0); i < 4; i++)
            {
                board[posX][posY+i] = 1;
            }
		//Colocando no arquivo
		std::ofstream myfile_2;
	       	myfile_2.open("the armada-format",std::ios_base::app);
	       	myfile_2 << "B" << " " << posX << " " << posY << " " << guidance << "\n";
	       	myfile_2.close();	    
        }

        /*Perceba que não existe uma função para verificar se existe barcos ao redor de onde este será spawnado, já que ele será o primeiro a ser colocado no board*/
    }   


    void Destroyer(std::vector<std::vector<int>> &board, int col, int row)
    {
        std::random_device rand;
		std::mt19937 seed(rand());		
		std::uniform_int_distribution <> picker1(1, col-1);
		std::uniform_int_distribution <> picker2(1, row - 2);
		std::uniform_int_distribution <> picker3(1, col - 2); 
        std::uniform_int_distribution <> V_or_H(0,1);		
        
        int checker(0);
	int posX(0);
	int posY(0);
        int guidance(0);
        int shadow(2);
        int qtdBoat(3); 

        for (size_t i = 0; i < qtdBoat; i++)
        {   
            guidance = V_or_H(seed);
            
            if(guidance == 0) 
            {   
                do  
                {                 

                    posX = picker2(seed);
                    posY = picker1(seed);

                    checker = 0;    
                    
                    for(int i(posX-1); i <= (posX+2); i++)
                    {
                        for (int j (posY-1); j <= (posY+1); j++)
                        {
                            if(board[i][j] == 1){
                                checker = board[i][j];
                                break;
                            }
                        }
                    }
                } while(checker == 1);
            
                for(int i(posX-1); i <= (posX+2); i++)
                {
                    for (int j (posY-1); j <= (posY+1); j++)
                    {
                        board[i][j] = shadow;
                    }
                }

                for(int i(0) ; i < 2; i++)
                {
                    	board[posX+i][posY] = 1;

                }
			//Colocando em um arquivo
			std::ofstream myfile_2;
		       	myfile_2.open("the armada-format",std::ios_base::app);
		       	myfile_2 << "D" << " " << posX << " " << posY << " " << guidance << "\n";
		       	myfile_2.close();
            } 
            else
            {
                do
                {  
                    posX = picker1(seed);
                    posY = picker3(seed);

                    checker = 0;

                    for(int i(posX-1); i <= (posX+1); i++)
                    {
                        for (int j (posY-1); j <= (posY+2); j++)
                        {
                            if(board[i][j] == 1){
                                checker = board[i][j];
                                break;
                            }
                        }
                    }
                } while(checker == 1);

               
               for(int i(posX-1); i <= (posX+1); i++)
                {
                    for (int j (posY-1); j <= (posY+2); j++)
                    {
                        board[i][j] = shadow;
                    }
                }

                for(int i(0); i < 2; i++)
                {
                    board[posX][posY+i] = 1;
                } 
		//Colocando em um arquivo
		std::ofstream myfile_2;
		myfile_2.open("the armada-format",std::ios_base::app);
		myfile_2 << "D" << " " << posX << " " << posY << " " << guidance << "\n";
		myfile_2.close();      
            }            
        }
    }


    void Crouiser(std::vector<std::vector<int>> &board, int col, int row)
    {
        std::random_device rand;
		std::mt19937 seed(rand());		
		std::uniform_int_distribution <> picker1(1, col - 1);
		std::uniform_int_distribution <> picker2(1, row - 3);
		std::uniform_int_distribution <> picker3(1, col - 3); 
        std::uniform_int_distribution <> V_or_H(0,1);		
        
        int checker(0); /* Variável auxiliar que irá chegar se os arredores de onde o barco irá spawnar possui um barco. 
                         Perceba que está variável irá percorrer os locais onde as "sombras" do barco estarão.*/

	// Coordenadas com valores base
	int posX(0);
	int posY(0);
        int guidance(0);
        int qtdBoat(2); // Quantidade de barcos que serão spawnados
        int shadow (2);

        for (size_t i = 0; i < qtdBoat; i++)
        {   
            guidance = V_or_H(seed);
            
            if(guidance == 0) 
            {   
                do  //Verificador de embarcações nos arredores da coordenada selecionada	
                {   //Este verificador analiza os barcos que serão colocados na Vertical                  

                    posX = picker2(seed);
                    posY = picker1(seed);

                    checker = 0;    // Reseta o Verificador		
                    
                    for(int i(posX-1); i <= (posX+3); i++)
                    {
                        for (int j (posY-1); j <= (posY+1); j++)
                        {
                            if(board[i][j] == 1){
                                checker = board[i][j];
                                break;
                                /*O elemento 0 na matriz representa a água, se o verificador achar algum elemento que não seja água nos 				arredores da embarcação,para a verificação e procura outra coordenada*/
                            }
                        }
                    }
                } while(checker == 1); // Enquanto achar barco;
            
                for(int i(posX-1); i <= (posX+3); i++)
                {
                    for (int j (posY-1); j <= (posY+1); j++)
                    {
                        board[i][j] = shadow;
                    }
                }

                //Spawna um Cruiser na posição Vertical.
                for(int i(0); i < 3; i++)
                {
                    board[posX+i][posY] = 1;
                }
		//Colocando em um arquivo
		std::ofstream myfile_2;
	       	myfile_2.open("the armada-format",std::ios_base::app);
	       	myfile_2 << "C" << " " << posX << " " << posY << " " << guidance << "\n";
	       	myfile_2.close();
            } 
            else
            {
                do
                {  //Este verificador analiza os barcos que serão colocados na Horizontal

                    posX = picker1(seed);
                    posY = picker3(seed);

                    checker = 0;

                    for(int i(posX-1); i <= (posX+1); i++)
                    {
                        for (int j (posY-1); j <= (posY+3); j++)
                        {
                            if(board[i][j] == 1){
                                checker = board[i][j];
                                break;
                            }
                        }
                    }
                } while(checker == 1);		

                for(int i(posX-1); i <= (posX+1); i++)
                {
                    for (int j (posY-1); j <= (posY+3); j++)
                    {
                        board[i][j] = shadow;
                    }
                }
                //Spawna um Cruiser na posição Horizontal.
                for(int i(0); i < 3; i++)
                {
                    board[posX][posY+i] = 1;
                } 
		//Colocando em um arquivo
		std::ofstream myfile_2;
	       	myfile_2.open("the armada-format",std::ios_base::app);
	       	myfile_2 << "C" << " " << posX << " " << posY << " " << guidance << "\n";
	       	myfile_2.close();    
            }            
        }
    }

    
    void Submarine(std::vector<std::vector<int>> &board, int col, int row)
    {
        std::random_device rand;
		std::mt19937 seed(rand());		
		std::uniform_int_distribution <> picker1(1, col - 1);
		std::uniform_int_distribution <> picker2(1, row - 1);
		std::uniform_int_distribution <> picker3(1, col - 1); 
        std::uniform_int_distribution <> V_or_H(0,1);		
        
        int checker(0);
	int posX(0);
	int posY(0);
        int shadow(2);
        int qtdBoat(4); 

        for (size_t i = 0; i < qtdBoat; i++)
        { 
            do  
            { 
                posX = picker2(seed);
                posY = picker1(seed);

                checker = 0;    
                
                for(int i(posX-1); i <= (posX+1); i++)
                {
                    for (int j (posY-1); j <= (posY+1); j++)
                    {
                        if(board[i][j] == 1 || board[i][j] == 3){ // Como mudamos o valor para representar o Submarine, a verificação muda para 			que um Submarine não exclua o outro.
                            checker = board[i][j];
                            break;
                        }
                    }
                }
            } while(checker == 1 || checker == 3);

        
             for(int i(posX-1); i <= (posX+1); i++)
                {
                    for (int j (posY-1); j <= (posY+1); j++)
                    {
                        board[i][j] = shadow;
                    }
                }

            board[posX][posY] = 3; // Usamos uma nomenclatura diferente para o Submarine para facilitar o print com os símbolos. 
		//Colocando em um arquivo
		std::ofstream myfile_2;
	       	myfile_2.open("the armada-format",std::ios_base::app);
	       	myfile_2 << "S" << " " << posX << " " << posY << "\n";
	       	myfile_2.close();
        }   
    }
}
