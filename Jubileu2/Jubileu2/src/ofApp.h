#pragma once


#include "ofMain.h"
#define Ninimigo 10
#define Menu 1
#define GamePlay 2
#define GameOver 3


class ofApp : public ofBaseApp
{


public:

	void setup();
	void update();
	void draw();



	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	//vetor da camera
	ofVec2f camera;

	//Imagens da HUD
	
	
	ofImage FundoMenu;

	int estadoJogo = GamePlay;

	//personagem completo
	struct personagem

	{
		ofVec2f posicao;
		ofVec2f vel;
		ofImage sprite;
		ofImage sprite2;
		ofImage lifeBarPlayer;
		ofImage lifePlayer;
		float tamanhoX, tamanhoY, tamanhoXLife, tamanhoYLife;
		float acele;
		int vida = 300, pontos = 0, dano = 1;
		bool Up = false; bool Down = false; bool Right = false; bool Left = false; bool Tiro = false;
		bool acompanhando = false; bool tiroDirecao = false; bool Ingame;
		
	};
	personagem player;
	personagem fundo;
	personagem PowerUp;

	struct monstros

	{
		ofVec2f posicao;
		ofVec2f vel;
		ofVec2f path;
		ofImage sprite;
		ofImage sprite2;
		ofImage EnemyBar;
		ofImage EnemyLife;
		float tamanhoX, tamanhoY, tamanhoXLife, tamanhoYLife;
		float acele;
		int vida = 600;
		int powerUpRandon = (0 + (rand () % Ninimigo));
		int powerUpRandon2 = (0 + (rand() % Ninimigo));
		bool Tiro = false;
		bool tiroDirecao = false; bool IniSub = false;
		bool IniDesc = false;
		bool IniDir = false; bool IniEsq = false; bool atingido = false;
		bool powerUpActive = false;
		bool iniVivo;
	};


	monstros inimigo[Ninimigo];



	struct golpes
	{
		ofVec2f posicao;
		ofVec2f vel;
		ofImage sprite;
		ofImage sprite2;
		float tamanhoX, tamanhoY;
		float acele;
		bool Tiro = false;
		bool acompanhando = false; bool Dir = false;
		bool powerUpAtkActive = false;
	};
	//preciso mudar esse nome de variavel
	golpes ataque;




	void desenhoNaTela(personagem& objeto, ofVec2f& mundo)
	{
		objeto.sprite.draw(objeto.posicao - mundo);
	}
	void desenhoPowerUp(personagem& objeto, ofVec2f mundo)
	{
		objeto.sprite2.draw(objeto.posicao - mundo);
	}
	void desenhoNaTelaTiro(golpes& objeto, ofVec2f& mundo, monstros& monstro)
	{
		if (monstro.powerUpActive == false)
			objeto.sprite.draw(objeto.posicao - mundo);
		else
			objeto.sprite2.draw(objeto.posicao - mundo);
	}
	void desenhoNaTelaMonstro(monstros& inimigo, ofVec2f& mundo)
	{
		
		if (inimigo.atingido == false)
			inimigo.sprite.draw(inimigo.posicao - mundo);
		else 
			inimigo.sprite2.draw(inimigo.posicao - mundo);
	}


	//FUNCAO DE COLISAO QUE PASSA O PLAYER E O QUE COLIDE
	void colisao(personagem& P1, monstros& P2)
	{

		//Colisao certa
		if (P1.posicao.x > P2.posicao.x - P2.tamanhoX && P1.posicao.x < P2.posicao.x + P2.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > P2.posicao.y - P2.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < P2.posicao.y + P2.tamanhoY)
		{
			//Se colidir com objeto volta uma posicao em y
			P1.posicao -= 2;
			P1.vida -= 2;
		}
	}

	//colisao com powerUp
	void colisaoPowerUp(personagem& P1, personagem& P2, monstros& mosntro)
	{

		//Colisao certa
		if (P1.posicao.x > P2.posicao.x - P2.tamanhoX && P1.posicao.x < P2.posicao.x + P2.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > P2.posicao.y - P2.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < P2.posicao.y + P2.tamanhoY)
		{
			//tiro.powerUpAtkActive = false;
			P2.Ingame = false;
			P1.dano = 2;
			mosntro.powerUpActive = true;
		}
	}
	void colisaoTiro(monstros& T1, golpes& P1, personagem& P2)
	{

		//Colisao certa
		if (P1.posicao.x > T1.posicao.x - T1.tamanhoX && P1.posicao.x < T1.posicao.x + T1.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > T1.posicao.y - T1.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < T1.posicao.y + T1.tamanhoY)
		{
			//Se colidir com objeto aumenta pontos, tira vida dos monstros e ativa a I.A 
			P2.pontos += 5;
			T1.vida -= P2.dano;
			T1.atingido = true;
			T1.IniDir = true;
		}
	}
	//funcao que o inimigo segue o player 
	void monstroSeguir(personagem jogador, monstros&  monstro)
	{
		monstro.path = jogador.posicao - monstro.posicao;
		monstro.path.normalize();
		monstro.vel += monstro.acele + abs(monstro.vel.x) + abs(monstro.vel.y);
		monstro.vel = monstro.path * monstro.vel.length();
	}

	void sorteioDrop(monstros& inimigo)
	{
		int sorteio = rand() % 100;

		if (sorteio < 50)
		{
			inimigo.powerUpActive = true;
			PowerUp.posicao = inimigo.posicao;
			PowerUp.Ingame = true;
		}
	}
	void travaTela(personagem& P1)
	{
		//travando em y
		if (P1.posicao.y > 1100)
		{
			P1.posicao.y -= 4;
		}
		else if (P1.posicao.y < 400)
		{
			P1.posicao.y += 4;
		}
		//travando o player na tela em x
		if (P1.posicao.x < 300)
		{
			P1.posicao.x += 4;
		}
	}


	void movimento(personagem& P1, golpes& T1)
	{
		if (P1.Up == true)
		{
			P1.vel.y -= P1.acele;
		}
		//movimenta para baixo
		if (P1.Down == true)
		{
			P1.vel.y += P1.acele;
		}
		//moviemnta para esquerda
		if (P1.Left == true)
		{

			P1.vel.x -= P1.acele;
		}
		//movimenta para direita (e so atira para direita)
		if (P1.Right == true)
		{
			P1.vel.x += P1.acele;
		}

		P1.vel.limit(500);
		//tiro movimenta se pressionado x
		if (T1.Tiro == true)
		{
			T1.vel.x = T1.acele;
		}
		//Tiro sempre segue o player
		if (T1.acompanhando == true)
		{
			T1.posicao = P1.posicao;
		}
	}

	void movimentoInimigo(monstros &inimigo, personagem& player)
	{
		inimigo.vel.limit(100);
		//movimento padrao para cima e para baixo
		if (inimigo.atingido == false && inimigo.posicao.distance(player.posicao) > 400)
		{
			if (inimigo.IniSub == true)
			{

				inimigo.vel.y -= inimigo.acele;
				if (inimigo.posicao.y < 400)
				{
					inimigo.vel.set(1, 1);
					inimigo.IniSub = false;
					inimigo.IniDesc = true;
				}
			}
			if (inimigo.IniDesc == true)
			{

				inimigo.vel.y += inimigo.acele;
				if (inimigo.posicao.y > 1100)
				{
					inimigo.vel.set(1, 1);
					inimigo.IniSub = true;
					inimigo.IniDesc = false;
				}
			}
		}
		else if(inimigo.atingido == false)
		{
			monstroSeguir(player, inimigo);
		}

		//Se o inimigo levar um tiro ele muda a I.A
		else 
		{
			inimigo.acele = 10.0f;
			
			if (inimigo.posicao.y < 400 || inimigo.posicao.y > 1100)
			{
				inimigo.atingido = false;
			}

			if (inimigo.IniDir == true)
			{
				inimigo.vel.y = 0;
				inimigo.vel.x += inimigo.acele;
				if (inimigo.posicao.x > 4000)
				{

					inimigo.vel.set(1, 1);
					inimigo.IniDir = false;
					inimigo.IniEsq = true;
				}
			}
			if (inimigo.IniEsq == true)
			{
				inimigo.vel.y = 0;
				inimigo.vel.x -= inimigo.acele;
				if (inimigo.posicao.x < 10)
				{

					inimigo.vel.set(1, 1);
					inimigo.IniDir = true;
					inimigo.IniEsq = false;
				}
			}
		}
	}

};