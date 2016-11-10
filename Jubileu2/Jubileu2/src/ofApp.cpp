#include "ofApp.h"

void ofApp::setup()
{


	//vida da HUD
	player.lifeBarPlayer.loadImage("players/BarraVida.png");
	player.lifePlayer.loadImage("players/Vida.png");
	player.lifeBarPlayer.resize(305, 80);
	player.lifePlayer.resize(2, 80);

	//Carregando as imagens de HUD dos inimigos
	for (int i = 0; i < Ninimigo; i++)
	{
		inimigo[i].EnemyBar.loadImage("players/LifeEnemyBar.png");
		inimigo[i].EnemyLife.loadImage("players/LifeEnemy.png");
		inimigo[i].EnemyBar.resize(100, inimigo[i].EnemyBar.getHeight());
		inimigo[i].EnemyLife.resize(14, inimigo[i].EnemyLife.getHeight());
	}


	//Imagem de fundo
	fundo.posicao.x = 0;
	fundo.posicao.y = 0;
	fundo.sprite.loadImage("Cenario/Rua2.png");
	FundoMenu.loadImage("Menu/FundoMenu.png");


	//definicoes padrao do player
	player.posicao.x = 600;
	player.posicao.y = 400;
	player.sprite.loadImage("players/Player.png");
	player.tamanhoY = player.sprite.getHeight() / 2;
	player.tamanhoX = player.sprite.getWidth() / 2;
	player.tamanhoXLife = player.lifePlayer.getWidth() / 2;
	player.tamanhoYLife = player.lifePlayer.getHeight() / 2;
	player.sprite.setAnchorPoint(player.sprite.getWidth() / 2, player.sprite.getHeight() / 2);
	player.acele = 20.0f;
	player.vida = 300;

	//definicoes powerUp de dano
	damageUp.damage.loadImage("players/PowerUpForca.png");
	damageUp.damage.setAnchorPoint(damageUp.damage.getWidth() / 2, damageUp.damage.getHeight() / 2);
	damageUp.tamanhoY = damageUp.damage.getHeight() / 2;
	damageUp.tamanhoX = damageUp.damage.getWidth() / 2;

	//definicoes da cura
	potion.heal.loadImage("players/PocaoVida.png");
	potion.heal.setAnchorPoint(potion.heal.getWidth() / 2, potion.heal.getHeight() / 2);
	potion.tamanhoY = potion.heal.getHeight() / 2;
	potion.tamanhoX = potion.heal.getWidth() / 2;
	potion.vida = rand() % 3;

	//definicoes padrao dos inimigos por vetores
	for (int i = 0; i < Ninimigo; i++)
	{

		inimigo[i].posicao.x = 900 + (rand() % 4072);
		inimigo[i].posicao.y = 100 + (rand() % 450);
		inimigo[i].sprite.loadImage("players/AlienVerde.png");
		inimigo[i].sprite2.loadImage("players/AlienAmarelo.png");
		inimigo[i].sprite3.loadImage("players/AlienVermelho.png");
		inimigo[i].tamanhoY = inimigo[i].sprite.getHeight() / 2;
		inimigo[i].tamanhoX = inimigo[i].sprite.getWidth() / 2;
		inimigo[i].tamanhoXLife = inimigo[i].EnemyLife.getWidth();
		inimigo[i].tamanhoYLife = inimigo[i].EnemyLife.getHeight();
		inimigo[i].sprite.setAnchorPoint(inimigo[i].sprite.getWidth() / 2, inimigo[i].sprite.getHeight() / 2);
		inimigo[i].sprite2.setAnchorPoint(inimigo[i].sprite2.getWidth() / 2, inimigo[i].sprite2.getHeight() / 2);
		inimigo[i].sprite3.setAnchorPoint(inimigo[i].sprite3.getWidth() / 2, inimigo[i].sprite3.getHeight() / 2);
		inimigo[i].acele = 1.0f;
		inimigo[i].IniSub = true;
		inimigo[i].vida = 30;

	}



	//definicoes do tiro
	ataque.sprite.loadImage("players/armaPlayer.png");
	ataque.sprite2.loadImage("players/armaPlayerUp1.png");
	ataque.tamanhoX = ataque.sprite.getHeight() / 2;
	ataque.tamanhoX = ataque.sprite.getWidth() / 2;
	ataque.sprite.setAnchorPoint(ataque.sprite.getWidth() / 2, ataque.sprite.getHeight() / 2);
	ataque.sprite2.setAnchorPoint(ataque.sprite2.getWidth() / 2, ataque.sprite2.getHeight() / 2);
	ataque.acele = 950.0f;
	ataque.acompanhando = true;


}

//--------------------------------------------------------------
void ofApp::update()
{
	switch (estadoJogo)
	{
	case Menu:

		break;

	case GamePlay:

		if (player.vida > 0)
		{
			//pegando tempo para usar na movimentação
			double time = ofGetLastFrameTime();

			//setando as posicoes x e y mais a velocidade multiplicada pelo tempo
			player.posicao += (player.dash + player.vel) * time;

			//dash 
			//dashVect(player);

			//camera do player
			camera = player.posicao - ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

			// velocidade do tiro multiplicada pelo tempo
			ataque.posicao += ataque.vel * time;

			//setando as posicoes x e y mais a velocidade multiplicada pelo tempo
			for (int i = 0; i < Ninimigo; i++)
			{
				inimigo[i].posicao += inimigo[i].vel * time;
			}


			//travando o player na tela em x,y
			travaTela(player);

			//se a tecla for pressionada o player moviemnta e atira
			movimento(player, ataque);

			//colisao com o power up
			for (int i = 0; i < Ninimigo; i++)
			{
				colisaoPowerUp(player, damageUp, inimigo[i]);
				colisaoPowerUp(player, potion, inimigo[i]);
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

			updateVector(player.dash, time);
		}
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

	case GamePlay:

		if (player.vida > 0)
		{


			//fundo do jogo
			desenhoNaTela(fundo, camera);

			//HUD
			for (int i = 0; i < player.vida; i++)
			{

				player.lifePlayer.draw(10 + (i * player.tamanhoXLife), 80);
				if (player.vida >= 300)
					player.vida = 300;
			}

			player.lifeBarPlayer.draw(10, 80);

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

			//Debugs para testes
			ofDrawBitmapString("Posicao do player: " + ofToString(player.posicao), 10, 10);
			ofDrawBitmapString("PONTOS: " + ofToString(player.pontos), 10, 50);
			ofDrawBitmapString("VIDA: " + ofToString(player.vida), 10, 70);
		}

		else if (player.vida <= 0)
			estadoJogo = GameOver;



		/*if (player.quant > 10)
		{
		ofBackground(0, 0, 0);
		ofDrawBitmapString("VOCE VENCEU!", 400, 300);
		}*/

		break;

	case GameOver:
	{
		ofBackground(0, 0, 0);
		ofDrawBitmapString("VOCE MORREU!", 400, 300);
	}
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
			estadoJogo = GamePlay;
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
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (estadoJogo)
	{
	case Menu:
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