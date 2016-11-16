#include "ofApp.h"

void ofApp::setup()
{
	//Imagem de fundo
	FundoMenu.loadImage("Menu/FundoMenu.png");
	fundo.posicao.x = 0;
	fundo.posicao.y = 0;
	fundo.street.loadImage("Cenario/Rua2.png");
	fundoTutorial.posicao.x = 0;
	fundoTutorial.posicao.y = 0;
	fundoTutorial.street.loadImage("Menu/FundoTutorial.png");



	//definicoes padrao do player
	player.continues = 3;
	player.lifeBarPlayer.loadImage("players/BarraVida2-3.png");
	player.lifeBarPlayer2.loadImage("players/BarraVida2-2.png");
	player.lifeBarPlayer3.loadImage("players/BarraVida2-1.png");
	player.lifePlayer.loadImage("players/Vida2.png");
	player.lifeBarPlayer.resize(305, 80);
	player.lifePlayer.resize(1, 40);
	player.posicao.x = 600;
	player.posicao.y = 700;
	player.sprite.loadImage("players/sprite_jogadorpack3.png");
	player.sprite.resize(1200, 300);
	player.tamanhoY = player.sprite.getHeight() / 2;
	player.tamanhoX = player.sprite.getWidth() / 9;
	player.tamanhoXLife = player.lifePlayer.getWidth() / 2;
	player.tamanhoYLife = player.lifePlayer.getHeight() / 2;
	player.sprite.setAnchorPoint(player.tamanhoXLife, player.tamanhoY);
	player.acele = 20.0f;
	player.vida = 400;
	player.walking.loadSound("Sonorizacao/Player_Running.WAV", true);
	player.shooting.loadSound("Sonorizacao/Boomerang_Player.WAV", true);

	//definicoes powerUp de dano
	damageUp.dano = 2;
	damageUp.damage.loadImage("players/PowerUpForca.png");
	damageUp.damage.setAnchorPoint(damageUp.damage.getWidth() / 2, damageUp.damage.getHeight() / 2);
	damageUp.tamanhoY = damageUp.damage.getHeight() / 2;
	damageUp.tamanhoX = damageUp.damage.getWidth() / 2;

	//definicoes da cura
	potion.heal.loadImage("players/PocaoVida.png");
	potion.heal.setAnchorPoint(potion.heal.getWidth() / 2, potion.heal.getHeight() / 2);
	potion.tamanhoY = potion.heal.getHeight() / 2;
	potion.tamanhoX = potion.heal.getWidth() / 2;
	potion.vida = (20 + (rand() % 40));

	//definicoes padrao dos inimigos por vetores
	for (int i = 0; i < Ninimigo; i++)
	{

		inimigo[i].posicao.x = 900 + (rand() % 5096);
		inimigo[i].posicao.y = 100 + (rand() % 450);
		inimigo[i].sprite.loadImage("players/Sprite_pack_inimigos.png");
		inimigo[i].sprite2.loadImage("players/Sprite_pack_inimigos-verdes.png");
		inimigo[i].sprite3.loadImage("players/Sprite_pack_inimigos-cinzas.png");
		inimigo[i].tamanhoY = inimigo[i].sprite.getHeight() / 6;
		inimigo[i].tamanhoX = inimigo[i].sprite.getWidth() / 3;
		inimigo[i].tamanhoXLife = inimigo[i].EnemyLife.getWidth();
		inimigo[i].tamanhoYLife = inimigo[i].EnemyLife.getHeight();
		inimigo[i].sprite.setAnchorPoint(inimigo[i].tamanhoX, inimigo[i].tamanhoY);
		inimigo[i].sprite2.setAnchorPoint(inimigo[i].tamanhoX, inimigo[i].tamanhoY);
		inimigo[i].sprite3.setAnchorPoint(inimigo[i].tamanhoX, inimigo[i].tamanhoY);
		inimigo[i].acele = 1.0f;
		inimigo[i].IniSub = true;
		inimigo[i].vida = 30;
		inimigo[i].EnemyBar.loadImage("players/LifeEnemyBar.png");
		inimigo[i].EnemyLife.loadImage("players/LifeEnemy.png");
		inimigo[i].EnemyBar.resize(100, inimigo[i].EnemyBar.getHeight());
		inimigo[i].EnemyLife.resize(14, inimigo[i].EnemyLife.getHeight());
	}

	inimigoTutorial.posicao.x = 700;
	inimigoTutorial.posicao.y = 700;
	inimigoTutorial.sprite.loadImage("players/Sprite_pack_inimigos.png");
	inimigoTutorial.sprite2.loadImage("players/Sprite_pack_inimigos-verdes.png");
	inimigoTutorial.sprite3.loadImage("players/Sprite_pack_inimigos-cinzas.png");
	inimigoTutorial.tamanhoY = inimigoTutorial.sprite.getHeight() / 6;
	inimigoTutorial.tamanhoX = inimigoTutorial.sprite.getWidth() / 3;
	inimigoTutorial.sprite.setAnchorPoint(inimigoTutorial.tamanhoX, inimigoTutorial.tamanhoY);

	//definicoes boss
	Boss.posicao.x = 7000;
	Boss.posicao.y = 700;
	Boss.spriteBoss.loadImage("players/Boss1.png");
	Boss.Bossbar.loadImage("players/LifeBarBoss.png");
	Boss.BossLife.loadImage("players/BossLife.png");
	Boss.BossLife.resize(2, 40);
	Boss.Bossbar.resize(670, 80);
	Boss.tamanhoX = Boss.spriteBoss.getWidth() / 4;
	Boss.tamanhoY = Boss.spriteBoss.getHeight();
	Boss.tamanhoXLife = Boss.BossLife.getWidth() / 3;
	Boss.tamanhoYLife = Boss.BossLife.getHeight();
	Boss.spriteBoss.setAnchorPoint(Boss.spriteBoss.getWidth() / 3, Boss.spriteBoss.getHeight());
	Boss.acele = 1.0f;
	Boss.vida = 1000;
	Boss.waveTime = 0;
	Boss.dano = 1;
	Boss.IniSub = true;
	Boss.scream.loadSound("Sonorizacao/Enemy_Scream.WAV", true);

	//definicoes do tiro
	ataque.sprite.loadImage("players/armaPlayer.png");
	ataque.sprite2.loadImage("players/armaPlayerUp1.png");
	ataque.tamanhoX = ataque.sprite.getHeight() / 2;
	ataque.tamanhoX = ataque.sprite.getWidth() / 2;
	ataque.sprite.setAnchorPoint(ataque.sprite.getWidth() / 2, ataque.sprite.getHeight() / 2);
	ataque.sprite2.setAnchorPoint(ataque.sprite2.getWidth() / 2, ataque.sprite2.getHeight() / 2);
	ataque.acele = 950.0f;
	ataque.acompanhando = true;

	//definicoes tiro boss
	for (int i = 0; i < 4; i++)
	{
		ataqueBoss[0].posicao.x = Boss.posicao.x - 150;
		ataqueBoss[0].posicao.y = Boss.posicao.y + 30;
		ataqueBoss[1].posicao.x = Boss.posicao.x - 50;
		ataqueBoss[1].posicao.y = Boss.posicao.y + 120;
		ataqueBoss[2].posicao.x = Boss.posicao.x + 50;
		ataqueBoss[2].posicao.y = Boss.posicao.y + 30;
		ataqueBoss[3].posicao.x = Boss.posicao.x - 40;
		ataqueBoss[3].posicao.y = Boss.posicao.y - 80;
		ataqueBoss[i].sprite.loadImage("players/armaPlayer.png");
		ataqueBoss[i].tamanhoX = ataqueBoss[i].sprite.getHeight() / 2;
		ataqueBoss[i].tamanhoX = ataqueBoss[i].sprite.getWidth() / 2;
		ataqueBoss[i].sprite.setAnchorPoint(ataqueBoss[i].sprite.getWidth() / 2, ataqueBoss[i].sprite.getHeight() / 2);
		ataqueBoss[i].acele = 1050.0f;
	}

}

//--------------------------------------------------------------
void ofApp::update()
{
	//pegando tempo para usar na movimentação
	double time = ofGetLastFrameTime();


	switch (estadoJogo)
	{
	case Tutorial:

		player.posicao += (player.dash + player.vel) * time;
		camera = player.posicao - ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		ataque.posicao += ataque.vel * time;
		movimento(player, ataque);
		player.temAnimacao += abs(player.vel.x) + abs(player.vel.y);
		updateVector(player.dash, time);
		animimarPlayer(player);
		colisao(player, inimigoTutorial);
		colisaoTiro(inimigoTutorial, ataque, player);
		travaTela(player);

		break;

	case GamePlay:

		if (player.vida > 0)
		{
			Boss.somTime += ofGetLastFrameTime();
			player.tempSom += abs(player.vel.x) + abs(player.vel.y);
			Boss.Tptime += ofGetLastFrameTime();
			player.temAnimacao += abs(player.vel.x) + abs(player.vel.y);

			for (int i = 0; i < Ninimigo; i++)
			{
				animarInimigos(inimigo[i]);
			}
			animimarPlayer(player);

			//som de passos
			/*if (player.tempSom > 30.0f)
			{
			player.walking.play();
			player.tempSom = 0.0f;
			}*/


			//setando as posicoes x e y mais a velocidade multiplicada pelo tempo
			player.posicao += (player.dash + player.vel) * time;

			//posicao boss
			Boss.posicao += Boss.vel * time;

			//camera do player
			camera = player.posicao - ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

			// velocidade do tiro multiplicada pelo tempo
			ataque.posicao += ataque.vel * time;
			for (int i = 0; i < 4; i++)
			{
				ataqueBoss[i].posicao += ataqueBoss[i].vel * time;
			}

			//travando o player na tela em x,y
			travaTela(player);

			//se a tecla for pressionada o player moviemnta e atira
			movimento(player, ataque);

			//colisao com o power up
			for (int i = 0; i < Ninimigo; i++)
			{
				inimigo[i].posicao += inimigo[i].vel * time;
				if (damageUp.colidir == false || potion.colidir == false)
				{
					colisaoPowerUp(player, damageUp, inimigo[i]);
					colisaoPowerUp(player, potion, inimigo[i]);
				}
			}

			//colisao com Boss
			colisao(player, Boss);
			playerTiroBoss(Boss, ataque, player);

			for (int i = 0; i < 4; i++)
			{
				colisaoTiroBoss(Boss, ataqueBoss[i], player);
			}


			//ALEATORIEDADE DAS FUNCOES
			for (int i = 0; i < Ninimigo; i++)
			{
				if (inimigo[i].vida > 0)
				{

					colisao(player, inimigo[i]);
					if (ataque.Tiro == true)
					{
						colisaoTiro(inimigo[i], ataque, player);
						if (inimigo[i].vida <= 0)
							sorteioDrop(inimigo[i]);
					}
					//Inimigo andando pela tela para cima e baixo
					movimentoInimigo(inimigo[i], player);

					if (inimigo[i].vida <= 10)
					{
						inimigo[i].dano = 4;
						inimigo[i].acele = 200.0f;
						monstroSeguir(player, inimigo[i]);
					}
				}
			}
			if (Boss.somTime > 10.0f)
			{
				Boss.scream.play();
				Boss.somTime = 0.0f;
			}
			//tiro do boss saindo em direcao ao player de tempos em tempos
			if (Boss.vida >= 600 && player.posicao.x >= 6000)
			{
				movimentoBoss(Boss);
				for (int i = 0; i < 4; i++)
				{
					iddle1(Boss, ataqueBoss[i]);
				}
			}
			else if (Boss.vida <= 600)
			{

				Boss.vel.limit(50);
				monstroSeguir(player, Boss);
				Boss.dano = 2;
				for (int i = 0; i < 4; i++)
				{
					iddle1(Boss, ataqueBoss[i]);
				}
			}
			if (Boss.vida <= 60 && player.vida <= 80)
				BossDrop(Boss, potion);




			//Dash parando
			updateVector(player.dash, time);
		}
		break;
	}
}


//--------------------------------------------------------------

void ofApp::draw()
{


	switch (estadoJogo)
	{
	case Menu:

		FundoMenu.draw(0, 0);
		break;
	case Tutorial:
		desenhoNaTelaFundo(fundoTutorial, camera);
		desenhoNaTela(player, camera);
		desenhoNaTelaMonstro(inimigoTutorial, camera);
		desenhoNaTelaTiro(ataque, camera, inimigoTutorial);
		ofDrawBitmapString("Posicao do player: " + ofToString(player.posicao), 10, 10);

		break;
	case GamePlay:

		if (player.vida > 0)
		{


			//fundo do jogo
			desenhoNaTelaFundo(fundo, camera);


			//HUD
			for (int i = 0; i < player.vida; i++)
			{
				player.lifePlayer.draw(100 + (i * player.tamanhoXLife), 110);
				if (player.vida >= 400)
					player.vida = 400;

			}
			if (player.continues >= 3)
				player.lifeBarPlayer.draw(10, 80);
			else if (player.continues == 2)
				player.lifeBarPlayer2.draw(10, 80);
			else
				player.lifeBarPlayer3.draw(10, 80);

			/*for (int i = 0; i < Boss.vida; i++)
			{
			Boss.BossLife.draw(10 + (i * Boss.tamanhoXLife), 120);
			}
			Boss.Bossbar.draw(10,120);*/

			//HUD ENEMYS
			for (int i = 0; i < Ninimigo; i++)
			{
				if (inimigo[i].vida > 0)
				{
					for (int j = 0; j < inimigo[i].vida; j++)
					{
						inimigo[i].EnemyLife.draw(((inimigo[i].posicao.x + (j * 3)) - 60) - camera.x, (inimigo[i].posicao.y - 70) - camera.y);
					}
					inimigo[i].EnemyBar.draw((inimigo[i].posicao.x - 60) - camera.x, (inimigo[i].posicao.y - 70) - camera.y);
				}
			}

			//power up desenhado na tela apos o inimigo morrer
			if (damageUp.Ingame == true)
				desenhoPowerUpDamage(damageUp, camera);
			else if (potion.Ingame == true)
				desenhoPowerUpPotion(potion, camera);

			desenhoNaTela(player, camera);

			for (int i = 0; i < Ninimigo; i++)
			{
				desenhoNaTelaTiro(ataque, camera, inimigo[i]);
			}

			//Desenhando inimigos
			for (int i = 0; i < Ninimigo; i++)
			{
				if (inimigo[i].vida > 0)
				{
					desenhoNaTelaMonstro(inimigo[i], camera);
				}
			}
			//desenhando o Boss com animacao
			if (Boss.vida > 0)
			{
				if (Boss.tempAnimacao > 600.0f)
				{
					Boss.frame += 1;
					if (Boss.frame > 4)
						Boss.frame = 0;
				}
				desenhoNaTelaBoss(Boss, camera);
				for (int i = 0; i < 4; i++)
				{
					desenhoNaTelaTiro(ataqueBoss[i], camera, Boss);
				}
			}


			//Debugs para testes
			ofDrawBitmapString("Posicao do player: " + ofToString(player.posicao), 10, 10);
			ofDrawBitmapString("PONTOS: " + ofToString(player.pontos), 10, 50);
			ofDrawBitmapString("BOSS VIDA: " + ofToString(Boss.vida), 10, 70);
		}

		else if (player.vida <= 0)
			estadoJogo = GameOver;

		break;

	case GameOver:

		if (player.continues >= 1)
		{
			ofBackground(0, 0, 0);
			ofDrawBitmapString("VOCE MORREU!", 400, 300);
			ofDrawBitmapString("Deseja continuar? ", 380, 350);
			ofDrawBitmapString("Sim / Nao", 400, 400);
			ofDrawBitmapString("Aperta S para sim e N para nao!", 350, 450);
			ofDrawBitmapString("Continues: " + ofToString(player.continues), 400, 500);

		}
		else
			ofDrawBitmapString("GAME OVER", 500, 300);
		break;

	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (estadoJogo)
	{
	case Menu:
		if (key == '1')
			estadoJogo = Tutorial;
		 if (key == '2')
			estadoJogo = GamePlay;
		 if (key == '3')
			break;
		break;
	case Tutorial:
		//se a tecla estiver sendo pressionada, movimenta
		if (key == OF_KEY_UP)
		{

			player.Up = true;
		}
		if (key == OF_KEY_DOWN)
		{

			player.Down = true;

		}
		if (key == OF_KEY_RIGHT)
		{

			player.Right = true;
			if (ataque.Tiro == false) {
				ataque.acele = 950.0f;
			}
		}
		if (key == OF_KEY_LEFT)
		{
			player.Left = true;
			if (ataque.Tiro == false) {
				ataque.acele = -950.0f;
			}
		}
		//tiro do personagem ativado e moviementa
		if (key == 'x' || key == 'X')
		{
			player.shooting.play();
			ataque.acompanhando = false;
			ataque.Tiro = true;
		}
		//Dashs em x e y 
		if (key == 'c')
			player.dash.set(600, 0);
		if (key == 'z')
			player.dash.set(-600, 0);
		if (key == 'a')
			player.dash.set(0, 600);
		if (key == 'd')
			player.dash.set(0, -600);
		if (key == 'm')
			estadoJogo = Menu;

		break;

	case GamePlay:
		//se a tecla estiver sendo pressionada, movimenta
		if (key == OF_KEY_UP)
		{
			
			player.Up = true;
		}
		if (key == OF_KEY_DOWN)
		{
			
			player.Down = true;

		}
		if (key == OF_KEY_RIGHT)
		{
			
			player.Right = true;
			if (ataque.Tiro == false) {
				ataque.acele = 950.0f;
			}
		}
		if (key == OF_KEY_LEFT)
		{
			player.Left = true;
			if (ataque.Tiro == false) {
				ataque.acele = -950.0f;
			}
		}
		//tiro do personagem ativado e moviementa
		if (key == 'x' || key == 'X')
		{
			player.shooting.play();
			ataque.acompanhando = false;
			ataque.Tiro = true;
		}
		//Dashs em x e y 
		if (key == 'c')
			player.dash.set(600, 0);
		if (key == 'z')
			player.dash.set(-600, 0);
		if (key == 'a')
			player.dash.set(0, 600);
		if (key == 'd')
			player.dash.set(0, -600);


		break;
	case GameOver:

		if (key == 's')
		{
			player.vida = 300;
			player.posicao.x = 600;
			player.posicao.y = 700;
			estadoJogo = GamePlay;
			player.continues -= 1;
		}
		if (key == 'n')
			break;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (estadoJogo)
	{
	case Tutorial:
		//se a telca não estiver sendo pressionada, para movimento
		if (key == OF_KEY_UP || key == 'w')
		{

			player.vel.y = 5;
			player.Up = false;
		}
		if (key == OF_KEY_DOWN || key == 's')
		{

			player.vel.y = 5;
			player.Down = false;
		}
		if (key == OF_KEY_RIGHT || key == 'd')
		{

			player.vel.x = 0;
			player.Right = false;
		}
		if (key == OF_KEY_LEFT || key == 'a')
		{

			player.vel.x = 0;
			player.Left = false;
		}
		if (key == 'x')
		{
			player.shooting.stop();
			ataque.acompanhando = true;
			ataque.Tiro = false;
		}

		break;
	case GamePlay:

		//se a telca não estiver sendo pressionada, para movimento
		if (key == OF_KEY_UP || key == 'w')
		{

			player.vel.y = 5;
			player.Up = false;
		}
		if (key == OF_KEY_DOWN || key == 's')
		{

			player.vel.y = 5;
			player.Down = false;
		}
		if (key == OF_KEY_RIGHT || key == 'd')
		{

			player.vel.x = 0;
			player.Right = false;
		}
		if (key == OF_KEY_LEFT || key == 'a')
		{

			player.vel.x = 0;
			player.Left = false;
		}
		if (key == 'x')
		{
			player.shooting.stop();
			ataque.acompanhando = true;
			ataque.Tiro = false;
		}

		break;

	case GameOver:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}