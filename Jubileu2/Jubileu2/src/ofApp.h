#pragma once


#include "ofMain.h"
#define Ninimigo 8
#define Menu 1
#define Tutorial 2
#define GamePlay 3
#define GameOver 4


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
		ofRectangle playerBox;
		float tamanhoX, tamanhoY, tamanhoXLife, tamanhoYLife, temAnimacao;
		float acele, tempSom, animacao, frame;
		int vida, pontos, dano, continues;
		bool Up = false; bool Down = false; bool Right = false; bool Left = false; bool Tiro = false;
		bool acompanhando = false; bool tiroDirecao = false; bool colison = false;
		bool covilBoss =  false;

	};
	personagem player;

	struct maps
	{
		ofVec2f posicao;
		ofImage street;
		bool bosslimit = false;
	};
	maps fundo;
	maps fundoTutorial;

	struct powerUp
	{
		bool Ingame; bool moredamage = false; bool cure = false; bool colidir = false;
		int dano;
		int vida;
		float tamanhoX, tamanhoY;
		ofVec2f posicao;
		ofImage damage;
		ofImage heal;
		ofRectangle powerupBox;
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
		ofRectangle mosntrosBox;
		float tamanhoX, tamanhoY, tamanhoXLife, tamanhoYLife;
		float acele, animaTime, waveTime, somTime, Tptime, frame, animacao, tempAnimacao;
		int vida, dano = 2, waitTime;
		bool IniSub = false;
		bool IniDesc = false;
		bool IniDir = false; bool IniEsq = false; bool atingido = false;
		bool powerUpActive = false; bool waveOn = false; 
	};


	monstros inimigo[Ninimigo];
	monstros inimigoTutorial;
	monstros Boss;

	//
	struct golpes
	{
		ofVec2f posicao;
		ofVec2f vel;
		ofVec2f path;
		ofImage sprite;
		ofImage sprite2;
		ofRectangle projetilBox;
		float tamanhoX, tamanhoY;
		float acele, angulo;
		bool Tiro = false;
		bool acompanhando = false; bool Dir = false;
		bool powerUpAtkActive = false;
	};
	
	golpes ataque;
	golpes ataqueBoss[4];

	void desenhoNaTela(personagem& objeto, ofVec2f& mundo)
	{
		objeto.sprite.drawSubsection(objeto.posicao.x - mundo.x, objeto.posicao.y - mundo.y, objeto.tamanhoX, objeto.tamanhoY, objeto.tamanhoX * objeto.frame, objeto.tamanhoY * objeto.animacao);
	}
	void desenhoNaTelaFundo(maps& objeto, ofVec2f& mundo)
	{
		objeto.street.draw(objeto.posicao - mundo);
		/*if (objeto.bosslimit == true)
			objeto.boss.draw(objeto.posicao - mundo);*/
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
		objeto.angulo = ofRadToDeg(atan2f(objeto.vel.y, objeto.vel.x));
		ofPushMatrix();
		ofTranslate(objeto.posicao - mundo);
		ofRotateZ(objeto.angulo);

		if (monstro.powerUpActive == false)
			objeto.sprite.draw(0, 0);
		else
			objeto.sprite2.draw(0, 0);

		ofPopMatrix();
	}
	void desenhoNaTelaMonstro(monstros& inimigo, ofVec2f& mundo)
	{

		if (inimigo.atingido == false)
			inimigo.sprite.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX * inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
		else
			inimigo.sprite2.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX * inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
		if (inimigo.vida <= 10)
			inimigo.sprite3.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX * inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
	}

	void desenhoNaTelaBoss(monstros& inimigo, ofVec2f& mundo)
	{
		inimigo.spriteBoss.drawSubsection(inimigo.posicao.x - mundo.x, inimigo.posicao.y - mundo.y, inimigo.tamanhoX, inimigo.tamanhoY, inimigo.tamanhoX *inimigo.frame, inimigo.tamanhoY * inimigo.animacao);
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
		/*if (P1.posicao.x > P2.posicao.x - P2.tamanhoX && P1.posicao.x < P2.posicao.x + P2.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > P2.posicao.y - P2.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < P2.posicao.y + P2.tamanhoY)*/
		//if(P2.posicao.distance(P1.posicao) < 150)
		if(P1.playerBox.intersects(P2.mosntrosBox))
		{
			//Se colidir perde vida
			P1.vida -= P2.dano;
		}
	}

	//colisao com powerUp
	void colisaoPowerUp(personagem& P1, powerUp& P2, monstros& mosntro)
	{

		//Colisao certa
		/*if (P1.posicao.x > P2.posicao.x - P2.tamanhoX && P1.posicao.x < P2.posicao.x + P2.tamanhoX &&
			P1.posicao.y + P1.tamanhoY > P2.posicao.y - P2.tamanhoY &&
			P1.posicao.y - P1.tamanhoY < P2.posicao.y + P2.tamanhoY)*/
		if(P1.playerBox.intersects(P2.powerupBox))
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
		
		////Colisao certa
		//if (P1.posicao.x > T1.posicao.x - T1.tamanhoX && P1.posicao.x < T1.posicao.x + T1.tamanhoX &&
		//	P1.posicao.y + P1.tamanhoY > T1.posicao.y - T1.tamanhoY &&
		//	P1.posicao.y - P1.tamanhoY < T1.posicao.y + T1.tamanhoY)
		if(P1.projetilBox.intersects(T1.mosntrosBox))
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
		if (Boss.vida >= 600)
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
		else if (Boss.vida < 200)
		{
			atakBoss.vel.limit(700);
			if (boss.waitTime >= 25)
			{
				posTiroBoss(ataqueBoss[0], boss);
				posTiroBoss(ataqueBoss[1], boss);
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
			//inimigo.powerUpActive = false;
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
			//Boss.powerUpActive = false;
			potion.posicao.x = (6200);
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

	void travatelaTutorial(personagem& P1)
	{
		if (P1.posicao.y > 1300)
		{
				P1.posicao.y -= 4;
				P1.vel.set(0, 0);
		}
		else if (P1.posicao.y < 400)
		{
				P1.posicao.y += 4;
				P1.vel.set(0, 0);
		}

		if (P1.posicao.x < 500)
		{
			P1.posicao.x += 4;
			P1.vel.set(0, 0);
		}
		if (P1.posicao.x > 1300)
		{
			P1.posicao.x -= 4;
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
	void animarInimigos(monstros& inimigo, personagem& player)
	{

		inimigo.tempAnimacao += abs(inimigo.vel.x) + abs(inimigo.vel.y);

		if (inimigo.tempAnimacao > 900.0f)
		{
			inimigo.frame += 1;
			inimigo.tempAnimacao = 0.0f;
			if (inimigo.frame > 2)
				inimigo.frame = 0;
		}
		if (inimigo.vel.x > 0)
			inimigo.animacao = 0;
		else if (inimigo.vel.x < 0)
			inimigo.animacao = 1;

		if (inimigo.vida <= 0)
		{
			inimigo.animacao = 5;
			inimigo.frame += 1;
			if (inimigo.frame > 2)
				inimigo.frame = 0;
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
		Boss.vel.limit(300);
		if (Boss.IniSub == true)
		{
			Boss.vel.y -= Boss.acele;
			if (Boss.posicao.y < 400)
			{
				Boss.vel.set(0,0);
				Boss.posicao.y += 4;
				Boss.IniSub = false;
				Boss.IniDesc = true;
			}
		}
		if (Boss.IniDesc == true)
		{
			Boss.vel.y += Boss.acele;
			if (Boss.posicao.y > 1100)
			{
				Boss.vel.set(0, 0);
				Boss.posicao.y -= 4;
				Boss.IniSub = true;
				Boss.IniDesc = false;
			}
		}

	}
	void boxColisoes(personagem& player, powerUp& damageUp, powerUp& potion, golpes& ataque, monstros& inimigo)
	{
		ataque.projetilBox.x = (ataque.posicao.x - ataque.tamanhoX);
		ataque.projetilBox.y = (ataque.posicao.y - ataque.tamanhoY);
		player.playerBox.x = (player.posicao.x - player.tamanhoX);
		player.playerBox.y = (player.posicao.y - player.tamanhoY);
		damageUp.powerupBox.x = (damageUp.posicao.x - damageUp.tamanhoX);
		damageUp.powerupBox.y = (damageUp.posicao.y - damageUp.tamanhoY);
		potion.powerupBox.x = (potion.posicao.x - potion.tamanhoX);
		potion.powerupBox.y = (potion.posicao.y - potion.tamanhoY);
		inimigo.mosntrosBox.x = (inimigo.posicao.x - inimigo.tamanhoX);
		inimigo.mosntrosBox.y = (inimigo.posicao.y - inimigo.tamanhoY);
		inimigo.mosntrosBox.x = (inimigo.posicao.x - inimigo.tamanhoX);
		inimigo.mosntrosBox.y = (inimigo.posicao.y - inimigo.tamanhoY);
		inimigo.mosntrosBox.x = (inimigo.posicao.x - inimigo.tamanhoX);
		inimigo.mosntrosBox.y = (inimigo.posicao.y - inimigo.tamanhoY);
	}
	void playerInGame(personagem& player, monstros& inimigo, double time)
	{
		//modulo de som por quantidade que andou
		player.tempSom += abs(player.vel.x) + abs(player.vel.y);
		//modulo de animacao pela quantidade que andou
		player.temAnimacao += abs(player.vel.x) + abs(player.vel.y);
		//animacao
		animimarPlayer(player);
		//setando as posicoes x e y mais a velocidade multiplicada pelo tempo
		player.posicao += (player.dash + player.vel) * time;
		// velocidade do tiro multiplicada pelo tempo
		ataque.posicao += ataque.vel * time;
		//camera do player
		camera = player.posicao - ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		//travando o player na tela em x,y
		travaTela(player);
		//se a tecla for pressionada o player moviemnta e atira
		movimento(player, ataque);

		//Dash parando
		updateVector(player.dash, time);
	}
	void inimigosInGame(monstros& inimigo, personagem& player, double time)
	{
		inimigo.posicao += inimigo.vel * time;
		inimigo.mosntrosBox.setPosition(inimigo.posicao);
		animarInimigos(inimigo, player);

		if (damageUp.colidir == false || potion.colidir == false)
		{
			colisaoPowerUp(player, damageUp, inimigo);
			colisaoPowerUp(player, potion, inimigo);
		}

		if (inimigo.vida > 0)
		{
			colisao(player, inimigo);
			if (ataque.Tiro == true)
			{
				colisaoTiro(inimigo, ataque, player);
				if (inimigo.vida <= 0)
					sorteioDrop(inimigo);
			}
			//Inimigo andando pela tela para cima e baixo
			movimentoInimigo(inimigo, player);

			if (inimigo.vida <= 10)
			{
				inimigo.dano = 3;
				inimigo.acele = 180.0f;
				monstroSeguir(player, inimigo);
			}
		}
	}
	void BossInGame(monstros& Boss, personagem& player, double time)
	{
		///Partes de velocidades, colisoes e tiros

		//tempo do som para efeitos
		Boss.somTime += ofGetLastFrameTime();
		//temo do teleporte do boss
		Boss.Tptime += ofGetLastFrameTime();
		//modulo de animacao por quantidade que andou
		Boss.tempAnimacao += abs(Boss.vel.x) + abs(Boss.vel.y);
		//posicao boss
		Boss.posicao += Boss.vel * time;
		//tiros do boss com velocidade multiplicada pelo tempo e colisao com os tiros no player
		for (int i = 0; i < 4; i++)
		{
			ataqueBoss[i].posicao += ataqueBoss[i].vel * time;
			colisaoTiroBoss(Boss, ataqueBoss[i], player);
		}
		//colisao com Boss
		colisao(player, Boss);
		playerTiroBoss(Boss, ataque, player);
		//Som dos boss na fase
		if (Boss.somTime > 10.0f)
		{
			Boss.scream.play();
			Boss.somTime = 0.0f;
		}

		///Acoes relacionadas com a vida do boss

		if (Boss.vida == 800 && player.posicao.x >= 6000)
		{
			movimentoBoss(Boss);
			for (int i = 0; i < 4; i++)
			{
				iddle1(Boss, ataqueBoss[i]);
			}
		}
		else if (Boss.vida <= 500)
		{
			Boss.vel.limit(200);
			monstroSeguir(player, Boss);
			Boss.dano = 2;
			for (int i = 0; i < 4; i++)
			{
				iddle1(Boss, ataqueBoss[i]);
			}
		}
		else if (Boss.vida <= 200)
		{
			Boss.vel.limit(300);
			monstroSeguir(player, Boss);
			Boss.dano = 3;
			for (int i = 0; i < 2; i++)
			{
				iddle1(Boss, ataqueBoss[i]);
			}
		}
		if (Boss.vida <= 500 && player.vida <= 80)
			BossDrop(Boss, potion);
	}
};