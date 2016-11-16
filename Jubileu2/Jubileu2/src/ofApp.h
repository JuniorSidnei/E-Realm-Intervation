#pragma once


#include "ofMain.h"
#define Ninimigo 6
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
		ofVec2f dash;
		ofImage sprite;
		ofImage sprite2;
		ofImage lifeBarPlayer;
		ofImage lifeBarPlayer2;
		ofImage lifeBarPlayer3;
		ofImage lifePlayer;
		ofSoundPlayer walking;
		ofSoundPlayer shooting;
		float tamanhoX, tamanhoY, tamanhoXLife, tamanhoYLife, temAnimacao;
		float acele, tempSom, animacao, frame;
		int vida, pontos = 0, dano = 1, continues;
		bool Up = false; bool Down = false; bool Right = false; bool Left = false; bool Tiro = false;
		bool acompanhando = false; bool tiroDirecao = false; bool colison = false; bool dashY; bool dashX;

	};
	personagem player;

	struct maps
	{
		ofVec2f posicao;
		ofImage street;
		ofImage boss;
		bool bosslimit = false;
	};
	maps fundo;

	struct powerUp
	{
		bool Ingame; bool moredamage = false; bool cure = false; bool colidir = false;
		int dano;
		int vida;
		float tamanhoX, tamanhoY;
		ofVec2f posicao;
		ofImage damage;
		ofImage heal;
	};
	powerUp damageUp;
	powerUp potion;

	struct monstros

	{
		ofVec2f posicao;
		ofVec2f vel;
		ofVec2f path;
		ofImage sprite;
		ofImage sprite2;
		ofImage sprite3;
		ofImage spriteBoss;
		ofImage Bossbar;
		ofImage BossLife;
		ofImage EnemyBar;
		ofImage EnemyLife;
		ofSoundPlayer scream;
		float tamanhoX, tamanhoY, tamanhoXLife, tamanhoYLife;
		float acele, animaTime, waveTime, somTime, Tptime, frame, animacao, tempAnimacao;
		int vida, dano = 2, waitTime;
		bool IniSub = false;
		bool IniDesc = false;
		bool IniDir = false; bool IniEsq = false; bool atingido = false;
		bool powerUpActive = false; bool waveOn = false;
	};


	monstros inimigo[Ninimigo];
	monstros Boss;

	//
	struct golpes
	{
		ofVec2f posicao;
		ofVec2f vel;
		ofVec2f path;
		ofImage sprite;
		ofImage sprite2;
		float tamanhoX, tamanhoY;
		float acele, angulo;
		bool Tiro = false;
		bool acompanhando = false; bool Dir = false;
		bool powerUpAtkActive = false;
	};
	//preciso mudar esse nome de variavel
	golpes ataque;
	golpes ataqueBoss[4];

	void desenhoNaTela(personagem& objeto, ofVec2f& mundo)
	{
		objeto.sprite.drawSubsection(objeto.posicao.x - mundo.x, objeto.posicao.y - mundo.y, objeto.tamanhoX, objeto.tamanhoY, objeto.tamanhoX * objeto.frame, objeto.tamanhoY * objeto.animacao);
	}
	void desenhoNaTelaFundo(maps& objeto, ofVec2f& mundo)
	{
		objeto.street.draw(objeto.posicao - mundo);
		if (objeto.bosslimit == true)
			objeto.boss.draw(objeto.posicao - mundo);
	}
	void desenhoPowerUpDamage(powerUp& objeto, ofVec2f mundo)
	{
		objeto.damage.draw(objeto.posicao - mundo);
	}
	void desenhoPowerUpPotion(powerUp& objeto, ofVec2f mundo)
	{
		objeto.heal.draw(objeto.posicao - mundo);
	}
	void desenhoNaTelaTiro(golpes& objeto, ofVec2f& mundo, monstros& monstro)
	{
		/*ofPushMatrix();
		ofTranslate(objeto.posicao);
		ofRotateZ(objeto.angulo);*/

		if (monstro.powerUpActive == false)
			objeto.sprite.draw(objeto.posicao - mundo);
		else
			objeto.sprite2.draw(objeto.posicao - mundo);
	}
	void desenhoNaTelaMonstro(monstros& inimigo, ofVec2f& mundo)
	{

		if (inimigo.atingido == false)
			//inimigo.sprite.draw(inimigo.posicao - mundo);
			inimigo.sprite.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX * inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
		else
			inimigo.sprite2.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX * inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
		if (inimigo.vida <= 10)
			inimigo.sprite3.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX * inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
	}

	void desenhoNaTelaBoss(monstros& inimigo, ofVec2f& mundo)
	{
		inimigo.spriteBoss.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.animaTime * 0, 0);
	}

	//parando o dash para não ser infinito
	void updateVector(ofVec2f& vec, float time)
	{
		if (vec.x > 0)
		{

			vec.x += (-player.acele * 40) * time;
			if (vec.x < 0)
				vec.x = 0;
		}
		else if (vec.x < 0) {

			vec.x += (player.acele * 40) * time;
			if (vec.x > 0)
				vec.x = 0;
		}

		if (vec.y > 0) {

			vec.y += (-player.acele * 40) * time;
			if (vec.y < 0)
				vec.y = 0;
		}
		else if (vec.y < 0) {

			vec.y += (player.acele * 40) * time;
			if (vec.y > 0)
				vec.y = 0;
		}
	}

	//FUNCAO DE COLISAO QUE PASSA O PLAYER E O QUE COLIDE
	void colisao(personagem& P1, monstros& P2)
	{

		//Colisao certa
		if (P1.posicao.x > P2.posicao.x - P2.tamanhoX && P1.posicao.x < P2.posicao.x + P2.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > P2.posicao.y - P2.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < P2.posicao.y + P2.tamanhoY)
		{
			//Se colidir perde vida
			P1.vida -= P2.dano;
		}
	}

	//colisao com powerUp
	void colisaoPowerUp(personagem& P1, powerUp& P2, monstros& mosntro)
	{

		//Colisao certa
		if (P1.posicao.x > P2.posicao.x - P2.tamanhoX && P1.posicao.x < P2.posicao.x + P2.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > P2.posicao.y - P2.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < P2.posicao.y + P2.tamanhoY)
		{
			P2.colidir = true;
			P2.Ingame = false;

			if (P2.moredamage == true)
			{
				mosntro.powerUpActive = true;
				P1.dano = P2.dano;
				P2.moredamage = false;
			}
			if (P2.cure == true)
			{
				P1.vida += P2.vida;
				P2.cure = false;
			}

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
			P2.colison = true;
			T1.vida -= P2.dano;
			T1.atingido = true;
			T1.IniDir = true;
		}
	}
	void playerTiroBoss(monstros& boss, golpes& atakplayer, personagem& player)
	{
		//T1 = boss
		//atakplayer = atakplayer
		//P2 = player

		//Colisao certa
		if (atakplayer.posicao.x > boss.posicao.x - boss.tamanhoX && atakplayer.posicao.x < boss.posicao.x + boss.tamanhoX &&
			atakplayer.posicao.y + atakplayer.tamanhoY > boss.posicao.y - boss.tamanhoY &&
			atakplayer.posicao.y - atakplayer.tamanhoY < boss.posicao.y + boss.tamanhoY)
		{
			//Se colidir com objeto aumenta pontos, tira vida dos monstros e ativa a I.A 
			player.colison = true;
			boss.vida -= player.dano;
			boss.atingido = true;
		}
	}
	void colisaoTiroBoss(monstros& Boss, golpes& atakBoss, personagem& player)
	{
		if (atakBoss.posicao.x > player.posicao.x - player.tamanhoX && atakBoss.posicao.x < player.posicao.x + player.tamanhoX &&
			atakBoss.posicao.y + atakBoss.tamanhoY > player.posicao.y - player.tamanhoY &&
			atakBoss.posicao.y - atakBoss.tamanhoY < player.posicao.y + player.tamanhoY)
		{
			player.colison = true;
			player.vida -= Boss.dano;
			if (player.colison == true)
				posTiroBoss(atakBoss, Boss);
		}
	}
	void posTiroBoss(golpes& atakBoss, monstros& Boss)
	{
		atakBoss.posicao.x = Boss.posicao.x - 150;
		atakBoss.posicao.y = Boss.posicao.y + 30;
		atakBoss.posicao.x = Boss.posicao.x - 50;
		atakBoss.posicao.y = Boss.posicao.y + 120;
		atakBoss.posicao.x = Boss.posicao.x + 50;
		atakBoss.posicao.y = Boss.posicao.y + 30;
		atakBoss.posicao.x = Boss.posicao.x - 40;
		atakBoss.posicao.y = Boss.posicao.y - 80;
	}

	//funcao que o inimigo segue o player 
	void monstroSeguir(personagem& jogador, monstros&  monstro)
	{

		monstro.path = jogador.posicao - monstro.posicao;
		monstro.path.normalize();
		monstro.vel += monstro.acele + abs(monstro.vel.x) + abs(monstro.vel.y);
		monstro.vel = monstro.path * monstro.vel.length();
	}
	void tiroBossSeguir(personagem& jogador, golpes& ataqueBoss)
	{
		ataqueBoss.path = jogador.posicao - ataqueBoss.posicao;
		ataqueBoss.path.normalize();
		ataqueBoss.vel += ataqueBoss.acele + abs(ataqueBoss.vel.x) + abs(ataqueBoss.vel.y);
		ataqueBoss.vel = ataqueBoss.path * ataqueBoss.vel.length();
	}

	void ataqueTiros(monstros& boss, golpes& atakBoss)
	{
		boss.waitTime += 1;
		tiroBossSeguir(player, atakBoss);
		if (Boss.vida >= 60)
		{
			atakBoss.vel.limit(500);
			if (boss.waitTime >= 15)
			{
				posTiroBoss(ataqueBoss[0], boss);
				posTiroBoss(ataqueBoss[1], boss);
				posTiroBoss(ataqueBoss[2], boss);
				posTiroBoss(ataqueBoss[3], boss);
				boss.waitTime = 0;
			}
		}
		else if (Boss.vida < 60 && Boss.vida >= 30)
		{
			atakBoss.vel.limit(600);
			if (boss.waitTime >= 25)
			{
				posTiroBoss(ataqueBoss[0], boss);
				posTiroBoss(ataqueBoss[1], boss);
				posTiroBoss(ataqueBoss[2], boss);
				posTiroBoss(ataqueBoss[3], boss);
				boss.waitTime = 0;
			}
		}
	}

	void sorteioDrop(monstros& inimigo)
	{
		int sorteio = rand() % 200;

		if (sorteio < 50)
		{
			inimigo.powerUpActive = true;
			damageUp.posicao = inimigo.posicao;
			damageUp.Ingame = true;
			damageUp.moredamage = true;
		}
		else if (sorteio > 50 && sorteio < 150)
		{
			inimigo.powerUpActive = false;
			potion.posicao = inimigo.posicao;
			potion.Ingame = true;
			potion.cure = true;
		}
	}
	void BossDrop(monstros& Boss, powerUp& potion)
	{
		int sort = rand() % 100;

		if (sort < 25)
		{
			potion.vida = (60 + rand() % 100);
			Boss.powerUpActive = false;
			potion.posicao.x = (620);
			potion.posicao.y = (500);
			potion.Ingame = true;
			potion.cure = true;
		}
	}
	void travaTela(personagem& P1)
	{
		//travando em y
		if (P1.posicao.y > 1100)
		{
			P1.posicao.y -= 4;
			P1.vel.set(0, 0);
		}
		else if (P1.posicao.y < 400)
		{
			P1.posicao.y += 4;
			P1.vel.set(0, 0);
		}
		//travando o player na tela em x
		if (P1.posicao.x < 500)
		{
			P1.posicao.x += 4;
			P1.vel.set(0, 0);
		}
	}


	void movimento(personagem& P1, golpes& T1)
	{
		if (P1.Up == true)
			P1.vel.y -= P1.acele;
		//movimenta para baixo
		if (P1.Down == true)
			P1.vel.y += P1.acele;
		//moviemnta para esquerda
		if (P1.Left == true)
			P1.vel.x -= P1.acele;
		//movimenta para direita
		if (P1.Right == true)
			P1.vel.x += P1.acele;
		P1.vel.limit(500);
		//Tiro sempre segue o player e se colidir com inimigo volta
		if (T1.acompanhando == true || P1.colison == true)
		{
			T1.posicao = P1.posicao;
			P1.colison = false;
		}
		//tiro movimenta se pressionado x
		else if (T1.Tiro == true)
			T1.vel.x = T1.acele;

	}
	void animimarPlayer(personagem& player)
	{

		if (player.temAnimacao > 1500.0f)
		{
			player.frame += 1;
			player.temAnimacao = 0.0f;
			if (player.frame > 8)
				player.frame = 1;
		}
		if (player.vel.x == 0 || player.vel.y == 0)
		{
			player.animacao = 0;
			player.frame = 0;
		}
		if (player.vel.x > 0)
			player.animacao = 0;
		else if (player.vel.x < 0)
			player.animacao = 1;
	}
	void animarInimigos(monstros& inimigo)
	{

		inimigo.tempAnimacao += abs(inimigo.vel.x) + abs(inimigo.vel.y);

		if (inimigo.tempAnimacao > 900.0f)
		{
			inimigo.frame += 1;
			inimigo.tempAnimacao = 0.0f;
		}
		if (inimigo.frame > 3)
			inimigo.frame = 0;
		if (inimigo.vel.x > 0)
			inimigo.animacao = 0;
		else if (inimigo.vel.x < 0)
			inimigo.animacao = 1;

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
		else if (inimigo.atingido == false)
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
	void iddle1(monstros& Boss, golpes& atakBoss)
	{
		Boss.waveTime += 1.0f;
		if (Boss.waveTime >= 120.0f)
		{

			ataqueTiros(Boss, ataqueBoss[0]);
			ataqueTiros(Boss, ataqueBoss[1]);
			ataqueTiros(Boss, ataqueBoss[2]);
			ataqueTiros(Boss, ataqueBoss[3]);
			Boss.waveTime = 0.0f;
		}
		if (Boss.waveTime == 0.0f)
			posTiroBoss(atakBoss, Boss);
	}
	void iddle3(monstros& Boss, personagem& player)
	{
		if (Boss.Tptime > 10.0f)
		{
			//Boss.posicao.x = (5600 + (rand () % 1800));
			//Boss.posicao.y = (500 + (rand () % 500));
			Boss.posicao.x = (500 + (rand() % 500));
			Boss.posicao.y = (400 + (rand() & 300));
			Boss.vel.limit(700);
			Boss.Tptime = 0.0f;
		}
	}
	void movimentoBoss(monstros& Boss)
	{
		Boss.vel.limit(200);
		if (Boss.IniSub == true)
		{
			Boss.vel.y -= Boss.acele;
			if (Boss.posicao.y < 400)
			{
				Boss.vel.set(1, 1);
				Boss.IniSub = false;
				Boss.IniDesc = true;
			}
		}
		if (Boss.IniDesc == true)
		{
			Boss.vel.y += Boss.acele;
			if (Boss.posicao.y > 1100)
			{
				Boss.vel.set(1, 1);
				Boss.IniSub = true;
				Boss.IniDesc = false;
			}
		}

	}

};