#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define LARGURA_TELA 640
#define ALTURA_TELA 480

/* ************************************************************************************************************************************************************************** */
void inicializacao(){
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_init_primitives_addon();

    DeuErro();
}
/* ************************************************************************************************************************************************************************** */
int DeuErro (){
    if(!al_init()){
        fprintf(stderr, "Falha init!\n");
        return 0;
    }

    if(!al_init_ttf_addon){
        fprintf(stderr, "Falha ttf!\n");
        return 0;
    }
    if(!al_is_keyboard_installed()){
        fprintf(stderr, "Falha keyboard!\n");
        return 0;
    }
    if(!al_is_mouse_installed()){
        fprintf(stderr, "Falha mouse!\n");
        return 0;
    }
    if(!al_init_image_addon()){
        fprintf(stderr, "Falha image!\n");
        return 0;
    }
    if(!al_init_primitives_addon()){
        fprintf(stderr, "Falha primitives!\n");
        return 0;
    }
    if (!al_install_audio()){
        fprintf(stderr, "Falha ao inicializar áudio\n");
        return 0;
    }
    if (!al_init_acodec_addon()){
        fprintf(stderr, "Falha ao inicializar codecs de áudio.n");
        return 0;
    }

} // Fim função DeuErro
/* ************************************************************************************************************************************************************************** */
// Variáveis globais
    //Necessarias
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_FONT *fontePixelGrande = NULL;
    ALLEGRO_FONT *fontePixel = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *imagem = NULL;
    ALLEGRO_BITMAP *imagem_iniciar = NULL;
    ALLEGRO_BITMAP *imagem_creditos = NULL;
    ALLEGRO_BITMAP *imagem_sair = NULL;
    ALLEGRO_BITMAP *imagem_tutorial = NULL;
    ALLEGRO_BITMAP *seta = NULL;
    ALLEGRO_BITMAP *prova = NULL;
    ALLEGRO_AUDIO_STREAM *musica = NULL;
    ALLEGRO_SAMPLE *sinal = NULL;
    ALLEGRO_SAMPLE *cachorro = NULL;
    ALLEGRO_SAMPLE *gato = NULL;
    ALLEGRO_SAMPLE *clique = NULL;
    ALLEGRO_SAMPLE *aplausos = NULL;
    bool fim = false;
    bool fim2 = false;

    //Variaveis de personagem
    char nome[200] = " ";
    int i=1;
    int sexo;
    int curso; // 1=exatas; 2=Humanas
    bool aprovado;
    int valor=0; //variavel do menu

    // Variaceis de consequência
    int DP=0;
    bool AjudaDP = false;
    bool ProjetoBom = false;
    bool Emprego = true;
    bool FuiNaMulti = false;
    bool MtoRoubado = true;
    bool Empreenda = false;
    bool EntregarProj = false;
    int ContadorDeFestas = 0;
    int ProgTCC = 0;
    bool PedirAjuda = false;
    bool DoTime = false;
    bool TeoriaPodcast = false;
    bool JogoLivro = false;
    bool dog = NULL;
/* ************************************************************************************************************************************************************************** */
int main(){
    inicializacao();

    //crição de dispositivos
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    fontePixelGrande = al_load_font("VCR_OSD_MONO.ttf", 30, 0);
    fontePixel = al_load_font("VCR_OSD_MONO.ttf", 21, 0);
    fila_eventos = al_create_event_queue();
    imagem = al_load_bitmap("telainicial.bmp");
    al_reserve_samples(1);

    //imagems do menu
    imagem_iniciar = al_load_bitmap("telainicial-iniciar.bmp");
    imagem_creditos = al_load_bitmap("telainicial-creditos.bmp");
    imagem_sair = al_load_bitmap("telainicial-sair.bmp");
    imagem_tutorial = al_load_bitmap("telainicial-tutorial.bmp");

    //cria o mixer
    if(!al_reserve_samples(6)){
        fprintf(stderr, "Falha ao alocar canais de áudio.n");
        thanos();
        return 0;
    }
     //carrega os samples
    sinal = al_load_sample( "Sinal.wav" );
    if (!sinal)
    {
     fprintf(stderr, "Falha ao carregar sample.n");
        thanos();
        return 0;
    }

    //carrega os samples
    gato = al_load_sample( "gato.wav" );
    if (!gato)
    {
     fprintf(stderr, "Falha ao carregar sample.n");
        thanos();
        return 0;
    }

    //carrega os samples
    cachorro = al_load_sample( "cachorro.wav" );
    if (!cachorro)
    {
     fprintf(stderr, "Falha ao carregar sample.n");
        thanos();
        return 0;
    }

    //carrega os samples
    clique = al_load_sample( "CLICKDOMOUSE.wav" );
    if (!clique)
    {
     fprintf(stderr, "Falha ao carregar clique.n");
        thanos();
        return 0;
    }

    aplausos = al_load_sample( "aplausos.wav" );
    if (!aplausos)
    {
     fprintf(stderr, "Falha ao carregar sample.n");
        thanos();
        return 0;
    }

    //registros de sources
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    //definição de dispositivos
    al_draw_bitmap(imagem, 0, 0, 0);
    al_set_window_title(janela, "Vida De Universitario");

    //definição de audio
    musica = al_load_audio_stream("Beliver imagine dragons.ogg", 4, 1024);
    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.n");
        thanos();
        return 0;
    }
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

    al_flip_display();
    int t;
    while(!fim){
        valor = menu();

        if(valor == 1){
                personagem();
                comecarjogo();
                fim2 = false;
        }

        else if (valor == 2){
                t = creditos();
                if(t == 3){
                    imagem = al_load_bitmap("telainicial.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);
                }
        }

        else if(valor == 3){
                fim = true;
        }
        else if(valor == 4){
            tutorial();
        }

    } //Fim do While
    thanos();
    return 0;
} // Fim função main
/* ************************************************************************************************************************************************************************** */
int menu(){
    while(!fim){
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);
        al_draw_bitmap(imagem, 0, 0, 0);

        //Menu Bonito (HOVER)
        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
            // START GAME
            if(ev.mouse.y > 240 && ev.mouse.y < 283 && ev.mouse.x > 193 && ev.mouse.x < 362){
                al_draw_bitmap(imagem_iniciar, 0, 0, 0);
                al_flip_display();
            }
            // CREDITOS
            else if(ev.mouse.y > 413 && ev.mouse.y < 459 && ev.mouse.x > 464 && ev.mouse.x < 629){
                al_draw_bitmap(imagem_creditos, 0, 0, 0);
                al_flip_display();
            }
            // QUIT
            else if(ev.mouse.y > 300 && ev.mouse.y < 343 && ev.mouse.x > 193 && ev.mouse.x < 363){
                al_draw_bitmap(imagem_sair, 0, 0, 0);
                al_flip_display();
            }
            // TUTORIAL
            else if(ev.mouse.y > 413 && ev.mouse.y < 459 && ev.mouse.x > 10 && ev.mouse.x < 175){
                al_draw_bitmap(imagem_tutorial, 0, 0, 0);
                al_flip_display();
            }
            else{
                al_draw_bitmap(imagem, 0, 0, 0);
                al_flip_display();
            }
        }

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
        }
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            // START GAME
            if(ev.mouse.y > 240 && ev.mouse.y < 283 && ev.mouse.x > 193 && ev.mouse.x < 362){
                valor = 1;
                return valor;
            }
            // CREDITOS
            if(ev.mouse.y > 413 && ev.mouse.y < 459 && ev.mouse.x > 464 && ev.mouse.x < 629){
                al_draw_text(fontePixel, al_map_rgb(252, 15, 192), LARGURA_TELA / 6, ALTURA_TELA / 1.75, ALLEGRO_ALIGN_CENTRE, "CREDITOS");
                valor = 2;
                return valor;
            }
            // QUIT
            if(ev.mouse.y > 300 && ev.mouse.y < 343 && ev.mouse.x > 193 && ev.mouse.x < 363){
                valor = 3;
                return valor;
                fim = true;
            }
            // TUTORIAL
            if(ev.mouse.y > 413 && ev.mouse.y < 459 && ev.mouse.x > 10 && ev.mouse.x < 175){
                valor = 4;
                return valor;
            }
        } // Fim do if "ALLEGRO_EVENT_MOUSE_BUTTON_DOWN"

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                fim = true;
            }
        }
        al_flip_display();
    } // Fim do While
} // Fim função menu
/* ************************************************************************************************************************************************************************** */
int personagem(){
    int validation = 0;
    int contEnter=0;

    imagem = al_load_bitmap("sexojogo.bmp");
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
    while(true){
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        //eventos de saida
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
            fim2 = true;
            break;
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                fim = true;
                fim2 = true;
                break;
            }
        }

        //input do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && validation == 0){

            if(ev.mouse.x > 230 && ev.mouse.y > 238 && ev.mouse.x < 301 && ev.mouse.y < 340){
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                al_draw_rectangle(230, 238, 301, 340, al_map_rgb(0,0,0), 2);
                sexo = 2;
            }
            else if (ev.mouse.x > 364 && ev.mouse.y > 238 && ev.mouse.x < 435 && ev.mouse.y < 340){
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                al_draw_rectangle(364, 238, 435, 340, al_map_rgb(0,0,0), 2);
                sexo = 1;
            }
        }

        //Input do teclado
         if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(validation == 0){

                if(ev.keyboard.keycode == ALLEGRO_KEY_A){
                strcat(nome, "A");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_B){
                strcat(nome, "B");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_C){
                strcat(nome, "C");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_D){
                strcat(nome, "D");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_E){
                strcat(nome, "E");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_F){
                strcat(nome, "F");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_G){
                strcat(nome, "G");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_H){
                strcat(nome, "H");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_I){
                strcat(nome, "I");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_J){
                strcat(nome, "J");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_K){
                strcat(nome, "K");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_L){
                strcat(nome, "L");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_M){
                strcat(nome, "M");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_N){
                strcat(nome, "N");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_O){
                strcat(nome, "O");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_P){
                strcat(nome, "P");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Q){
                strcat(nome, "Q");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_R){
                strcat(nome, "R");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_S){
                strcat(nome, "S");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_T){
                strcat(nome, "T");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_U){
                strcat(nome, "U");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_V){
                strcat(nome, "V");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_W){
                strcat(nome, "W");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_X){
                strcat(nome, "X");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Y){
                strcat(nome, "Y");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Z){
                strcat(nome, "Z");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }

            }

            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                strcat(nome, " ");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
             if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                    if(i>1){
                        nome[i-1] = NULL;
                        i--;
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                        al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 160, ALLEGRO_ALIGN_CENTRE, nome);
                    }
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER){
                if (i > 1){
                        validation = 1;
                        contEnter=contEnter+1;
                        imagem = al_load_bitmap("confirma.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Eu me chamo%s", nome);

                        if (sexo == 1){
                            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu sou do sexo masculino");
                        }
                        else if (sexo == 2) {
                            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu sou do sexo feminino");
                        }
                        else {
                            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu nao tenho sexo definido");
                        }
                        if(contEnter == 2){
                            break;
                        }
                }
            } // Fim do if "ALLEGRO_KEY_ENTER"
            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT || ev.keyboard.keycode == ALLEGRO_KEY_RSHIFT){
                    validation=0;
                    contEnter=0;
                    while(i!=1){
                        nome[i-1] = NULL;
                        i--;
                    }
                    imagem = al_load_bitmap("sexojogo.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);
                    al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
            }
         } // Fim do If de input do teclado
        al_flip_display();
    } //Fim do While
} // Fim função Personagem
/* ************************************************************************************************************************************************************************** */
// Cartas e fluxo do jogo

//variaveis influenciadas  //tipo
    int inteligencia=50;  // = 1
    int fama=50;          // = 2
    int dinheiro=50;      // = 3

//variaveis globais para o fluxo
        int fluxo = 0;
        int atual = 1;
        int uso=0;
        int x=320;
        int y = 480;

typedef struct{
    int num;
    char texto[100];
    int esc1_tipo1;
    int valor1_esc1;
    int esc1_tipo2;
    int valor2_esc1;
    int esc2_tipo1;
    int valor1_esc2;
    int esc2_tipo2;
    int valor2_esc2;
    int consequenciaRight;
    int consequenciaLeft;
}info;
/* ************************************************************************************************************************************************************************** */
//dando informações as cartas
info cartas[64] = {
    //{Numero da carta,texto da carta, atributo1, valor do atributo1, atributo2, valor do atributo2, atributo1, valor do atributo 1, atributo2, valor do atributo2, consequencia},
    {0,"cartas/1.bmp", 11, 10, NULL, NULL, 22, 10, NULL, NULL, NULL, NULL},
    {1, "cartas/curso.bmp", 14, 2, NULL, NULL,14 ,1, NULL, NULL, NULL, NULL},
    {2, "cartas/2.bmp", 11, 5, NULL, NULL,22 ,5, 23, -20, NULL, NULL},
    {3, "cartas/3.bmp", 12, 10, NULL, NULL, 22 ,5, NULL, NULL, 30, NULL},
    {4, "cartas/4.bmp", 11, 10, 12, -5, 21 , 20, 22, -10, NULL, NULL},
    {5, "cartas/5.bmp", 11, 10, 12, -5, 22 ,10, NULL, NULL, 40, 32},
    {6, "cartas/prova.bmp", 15, 0, NULL, NULL, 25, 1, NULL, NULL, NULL, 38},
    {7, "cartas/0.bmp", 15, 0, NULL, NULL, 25, 1, NULL, NULL, NULL, NULL},
    {8, "cartas/ferias.bmp", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {9, "cartas/6.bmp", 12, 10, 11, -10, 22,-10, 21, 10, NULL, NULL},
    {10, "cartas/7.bmp", 11, -10, NULL, NULL ,21 ,10, NULL, NULL, 31, NULL},
    {11, "cartas/8.bmp", 11, 20, NULL, NULL,21 , -10, 22, 5, NULL, NULL},
    {12, "cartas/prova.bmp", 15, 1, NULL, NULL,25 ,0, NULL, NULL, NULL, NULL},
    {13, "cartas/0.bmp", 15, 1, NULL, NULL, 25, 0, NULL, NULL, NULL, NULL},
    {14, "cartas/ferias.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL, NULL, NULL},
    {15, "cartas/9.bmp", 12, 5, NULL, NULL, 21, 5, NULL, NULL, NULL, 33}, //3 semestre
    {16, "cartas/10.bmp", 11, -5, NULL, NULL,21 ,10, NULL, NULL, NULL, NULL},//folga do trabalho
    {17, "cartas/11.bmp", 11, -10, NULL, NULL, 21, 10, 22, 10, NULL, 40},
    {18, "cartas/prova.bmp", 15, 0, NULL, NULL, 25, 1, NULL, NULL, NULL, NULL},
    {19, "cartas/0.bmp", 11, 0, NULL, NULL, 22,0, NULL, NULL, NULL, NULL},
    {20, "cartas/ferias.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL, NULL, NULL},
    {21, "cartas/12.bmp", 12, 8, 13, 10, 21,5, NULL, NULL, 35, 36},//4 semestre
    {22, "cartas/0.bmp", 11, 0, NULL, NULL, 22,0, NULL, NULL, NULL, NULL},
    {23, "cartas/13.bmp", 11, 0, NULL, NULL, 23, -5, NULL, NULL, NULL, NULL},
    {24, "cartas/14.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL, NULL, 34},
    {25, "cartas/MtoRoubado.bmp", 13, -10, NULL, NULL, 23 ,-10, NULL, NULL, NULL, NULL},
    {26, "cartas/prova.bmp", 15, 0, NULL, NULL, 25 ,1, NULL, NULL, NULL, NULL},
    {27, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {28, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {29, "cartas/15.bmp", 12, 10, NULL, NULL, 22 , -10, NULL, NULL, NULL, NULL}, //5 semestre
    {30, "cartas/16.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, 42, 41},
    {31, "cartas/17.bmp", 12, 15, 13, -15, 22 , -5, NULL, NULL, NULL, 40},
    {32, "cartas/prova.bmp", 15, 1, NULL, NULL, 25 ,0, NULL, NULL, NULL, NULL},
    {33, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {34, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {35, "cartas/18.bmp", 12, 10, NULL, NULL, 22 ,-10, NULL, NULL, NULL, NULL}, //6 semestre
    {36, "cartas/19.bmp", 12, 5, 13, -5, 21 , 5, 22, -2, NULL, 40},
    {37, "cartas/20.bmp", 11, -15, NULL, NULL, 21, 10, NULL, NULL, NULL, NULL},
    {38, "cartas/prova.bmp", 15, 1, NULL, NULL, 25 ,0, NULL, NULL, NULL, NULL},
    {39, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {40, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {41, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, 52, 51}, //7 semestre
    {42, "cartas/22.bmp", 13, -10, 22, 15, 22 ,-15, NULL, NULL, NULL, NULL},
    {43, "cartas/23.bmp", 12, 5, NULL, NULL, 21 , 2, NULL, NULL, 50, NULL},
    {44, "cartas/prova.bmp", 15, 0, NULL, NULL, 25 ,1, NULL, NULL, NULL, NULL},
    {45, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {46, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {47, "cartas/24.bmp", 13, 20, NULL, NULL, 23, -20, NULL, NULL, NULL, NULL}, //8 semestre
    {48, "cartas/25.bmp", 12, -1, NULL, NULL, 23, -10, NULL, NULL, 50, 37},
    {49, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {50, "cartas/26.bmp", 11, 10, NULL, NULL, 22 , 5, NULL, NULL, 50, NULL},
    {51, "cartas/prova.bmp", 15, 1, NULL, NULL, 25 ,0, NULL, NULL, NULL, NULL},
    {52, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {53, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {54, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {55, "cartas/0.bmp", 15, 1, NULL, NULL, 25 ,0, NULL, NULL, NULL, NULL},
    {56, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {57, "cartas/0.bmp", 15, 1, NULL, NULL, 25 ,0, NULL, NULL, NULL, NULL},
    {58, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {59, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {60, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {61, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {62, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    {63, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL, NULL, NULL},
    };
/* ************************************************************************************************************************************************************************** */
typedef struct{
    int num;
    char texto[100];
}infoTutorial;
/* ************************************************************************************************************************************************************************** */
infoTutorial cartasTutorial[9] = {
    {0, "cartas/Tutorial/Tut1.bmp"},
    {1, "cartas/Tutorial/Tut2.bmp"},
    {2, "cartas/Tutorial/Tut3.bmp"},
    {3, "cartas/Tutorial/Tut6.bmp"},
    {4, "cartas/Tutorial/Tut4.bmp"},
    {5, "cartas/Tutorial/Tut7.bmp"},
    {6, "cartas/Tutorial/Tut8.bmp"},
    {7, "cartas/Tutorial/Tut5.bmp"},
    {8, "cartas/Tutorial/Tut5.bmp"},
};
/* ************************************************************************************************************************************************************************** */
int tutorial(){
    int posicao = 0;
    imagem = al_load_bitmap(cartasTutorial[posicao].texto);
    al_draw_bitmap(imagem, 0, 0, 0);
    while(true){
            ALLEGRO_EVENT ev;
            al_wait_for_event(fila_eventos, &ev);

            if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        fim = true;
                        break;
                    }
            }
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    fim = true;
                    break;
            }

            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                posicao++;
                imagem = al_load_bitmap(cartasTutorial[posicao].texto);
                al_draw_bitmap(imagem, 0, 0, 0);

                if(posicao == 2){
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
                }
                if(posicao == 3){
                    al_draw_textf(fontePixel, al_map_rgb(255, 166, 34), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
                    al_draw_textf(fontePixel, al_map_rgb(255, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
                }
            }
            if(posicao == 8){
                imagem = al_load_bitmap("telainicial.bmp");
                break;
            }
            al_flip_display();
    } // Fim do While
}
/* ************************************************************************************************************************************************************************** */
int mostrar_status(){
    /*
    muda para amarelo ou vermelho os atributos em zonas de perigo
    < 20 - vermelho, gameover
    > 80 - amarelo, "gamewon"
    */

    ALLEGRO_COLOR vermelho = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR amarelo = al_map_rgb(255, 166, 34);
    ALLEGRO_COLOR preto = al_map_rgb(0, 0, 0);

    if(inteligencia <= 20){
        al_draw_textf(fontePixel, vermelho, 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
    }else if(inteligencia >= 80){
        al_draw_textf(fontePixel, amarelo, 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
    }else{
        al_draw_textf(fontePixel, preto, 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
    }

    if(fama <= 20){
        al_draw_textf(fontePixel, vermelho, 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
    }else if(fama >= 80){
        al_draw_textf(fontePixel, amarelo, 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
    }else{
        al_draw_textf(fontePixel, preto, 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
    }

    if(dinheiro <= 20){
        al_draw_textf(fontePixel, vermelho, 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
    }else if(dinheiro >= 80){
        al_draw_textf(fontePixel, amarelo, 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
    }else{
        al_draw_textf(fontePixel, preto, 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
    }

    if(DP >= 2){
        al_draw_textf(fontePixel, vermelho, 530, 100, ALLEGRO_ALIGN_CENTER, "DPs: %d", DP);
    }else{
        al_draw_textf(fontePixel, preto, 530, 100, ALLEGRO_ALIGN_CENTER, "DPs: %d", DP);
    }

    al_draw_textf(fontePixelGrande, preto, LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);

}
/* ************************************************************************************************************************************************************************** */
void escolha(int tipo1, int valor1, int tipo2,int valor2, int consequencia){
    if(tipo1 < 20 || tipo2 < 20){ // SIGNIFICA QUE NÃO É A ESCOLHA 2
            if(tipo1 == 11){
                inteligencia = inteligencia + valor1;
            }
            if(tipo1 == 12){
                fama = fama + valor1;
            }
            if(tipo1 == 13){
                dinheiro = dinheiro + valor1;
            }
            if(tipo2 == 11){
                inteligencia = inteligencia + valor2;
            }
            if(tipo2 == 12){
                fama = fama + valor2;
            }
            if(tipo2 == 13){
                dinheiro = dinheiro + valor2;
            }
            if(tipo1 == 14){ //Criada especificamente para escolher o curso
                curso = valor1;
            }
            if (tipo1 == 15){ //Criada especificamente para provas
                aprovado = valor1;
            }
    }
    if(tipo1 > 20 || tipo2 > 20){ // SIGNIFICA QUE É A ESCOLHA 2
            if(tipo1 == 21){
                inteligencia = inteligencia + valor1;
            }
            if(tipo1 == 22){
                fama = fama + valor1;
            }
            if(tipo1 == 23){
                dinheiro = dinheiro + valor1;
            }
            if(tipo2 == 21){
                inteligencia = inteligencia + valor2;
            }
            if(tipo2 == 22){
                fama = fama + valor2;
            }
            if(tipo2 == 23){
                dinheiro = dinheiro + valor2;
            }
            if(tipo1 == 24){ //Criada especificamente para escolher o curso
                curso = valor1;
            }
            if (tipo1 == 25){ //Criada especificamente para provas
                aprovado = valor1;
            }
    }
    if(consequencia == 30){
        AjudaDP = true;
    }
    if(consequencia == 31){
        Emprego = false;
    }
    if(consequencia == 32){
        ProjetoBom = true;
    }
    if(consequencia == 33){
        FuiNaMulti = true;
    }
    if(consequencia == 34){
        MtoRoubado = false;
    }
    if(consequencia == 35){
        EntregarProj = true;
    }
    if(consequencia == 36){
        Empreenda = true;
    }
    if(consequencia == 37){
        PedirAjuda = true;
    }
    if(consequencia == 38){
        DoTime = true;
    }
    if(consequencia == 40){
        ContadorDeFestas = ContadorDeFestas + 1;
    }
    if(consequencia >= 50){
        if(consequencia == 51){
            JogoLivro = true;
            if(atual != fluxo){
                ProgTCC = ProgTCC + 35;
                atual = fluxo;
            }
        }
        if(consequencia == 52){
            TeoriaPodcast = true;
            if(atual != fluxo){
                ProgTCC = ProgTCC + 35;
                atual = fluxo;
            }
        }
        if (consequencia == 50){
            if(atual != fluxo){
                ProgTCC = ProgTCC + 35;
                atual = fluxo;
            }
        }

    }
    if(consequencia == 41){
        dog = true;
    }
    else if(consequencia == 42){
        dog = false;
    }
} // Fim função escolha
/* ************************************************************************************************************************************************************************** */
int conseq_aprovacao(){

    if(fluxo == 7 || fluxo == 13 || fluxo == 19 || fluxo == 27 || fluxo == 33 || fluxo == 39 || fluxo == 45 || fluxo == 52){
        if(aprovado == 0){
            if(ProjetoBom == true){//Consequencia ter feito projeto
                imagem = al_load_bitmap("cartas/ProjetoBom.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if(AjudaDP == true){//Consequencia amizade com pessoal da frente
                imagem = al_load_bitmap("cartas/semestre-completo-ajuda.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                uso = 1;
            }
            else{
                imagem = al_load_bitmap("cartas/semestre-reprovado.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                if(atual != fluxo){
                    DP++;
                    atual = fluxo;
                }
            }
        } //Fim do if "aprovado == 0"
        else if(aprovado == 1){
            imagem = al_load_bitmap("cartas/semestre-completo.bmp");
            al_play_sample(aplausos, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            al_draw_bitmap(imagem, 0, 0, 0);
        }

        mostrar_status();
        if(fluxo > 41){
            al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 483, 120, ALLEGRO_ALIGN_LEFT, "TCC: %d", ProgTCC);
            al_draw_circle(590, 124, 3, al_map_rgb(0,0,0), 2);
            al_draw_circle(600, 135, 3, al_map_rgb(0, 0, 0), 2);
            al_draw_line(590, 135, 600, 124, al_map_rgb(0, 0, 0), 2);
        }

    } //Fim if de fluxo
} // Fim da função conseq_aprovacao
/* ************************************************************************************************************************************************************************** */
int resetar(){

    fluxo = 0;
    inteligencia = 50;
    dinheiro = 50;
    fama = 50;
    sexo = NULL;
    atual = 1;
    uso = 0;
    curso = NULL;
    aprovado = NULL;
    valor = 0;
    while(i!=1){
        nome[i-1] = NULL;
        i--;
    }

    // Variaceis de consequência
    DP=0;
    AjudaDP = false;
    ProjetoBom = false;
    Emprego = true;
    FuiNaMulti = false;
    MtoRoubado = true;
    Empreenda = false;
    EntregarProj = false;
    ContadorDeFestas = 0;
    ProgTCC = 0;
    PedirAjuda = false;
    DoTime = false;
    TeoriaPodcast = false;
    JogoLivro = false;
    x = 320;
    y = 480;
}
/* ************************************************************************************************************************************************************************** */
int conseq_endgame(){

    if(inteligencia <= 0 || dinheiro <= 0 || fama <= 0 ||
    inteligencia > 100 || dinheiro > 100 || fama > 100 ||
    DP == 3 || ProgTCC < 100){

        // game over
        if(DP == 3){
            imagem = al_load_bitmap("cartas/consequencia_finais/dp.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
            al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
        }else
            if(inteligencia <= 0){
                imagem = al_load_bitmap("cartas/consequencia_finais/inteligencia0.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
            }else if(dinheiro <= 0){
                imagem = al_load_bitmap("cartas/consequencia_finais/dinheiro0.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
            }else if(fama <= 0){
                imagem = al_load_bitmap("cartas/consequencia_finais/fama0.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
            }else if(fama > 100){
                imagem = al_load_bitmap("cartas/consequencia_finais/fama100.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
            }else

            //game won
            if(inteligencia > 100){
                imagem = al_load_bitmap("cartas/consequencia_finais/inteligencia100.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
            }else if(dinheiro > 100){
                imagem = al_load_bitmap("cartas/consequencia_finais/dinheiro100.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
            }
    }
} // Fim da função conseq_endgame
/* ************************************************************************************************************************************************************************** */
int conseq_fluxo(){
//consequencias do decorrer do fluxo

    //não ter feito os relatórios
    if(fluxo == 16){
        if(Emprego == false){
            imagem = al_load_bitmap("cartas/desempregado.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
        }
    }
    // Ser ajudado numa DP
    if((fluxo == 8 || fluxo == 14) && uso == 1 && AjudaDP == true){
        AjudaDP = false;
    }
    // Ter feito o projeto pra te livrar da DP no primeiro semestre
    if(fluxo == 8){
        ProjetoBom = false;
    }
    // Ter ido na multinacional
    if(fluxo == 28){
        if(FuiNaMulti == true && Emprego == false){
            imagem = al_load_bitmap("cartas/GanhaEmpregoMulti.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
        }
    }
    // Roubado
    if(fluxo == 25){
        if(MtoRoubado == false){
            imagem = al_load_bitmap("cartas/PoucoRoubado.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
        }
    }
    if(fluxo == 26 && MtoRoubado == false){
        if(atual != fluxo){
            dinheiro = dinheiro + 5;
            atual = fluxo;
        }
    }
    // Empreender ou entregar como projeto
    if(fluxo == 22){
        if(EntregarProj == true){
            if(DP >= 1){
                imagem = al_load_bitmap("cartas/EmpreendaComDP.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                if(atual != fluxo){
                    DP--;
                    atual = fluxo;
                }
            }
            else{
                imagem = al_load_bitmap("cartas/EmpreendaSemDP.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }else if(Empreenda == true){
            imagem = al_load_bitmap("cartas/Empreendendo.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
        }
    }

    // Carta de TCC dependendo do curso
    if(fluxo == 41){
        if(curso == 1){
            imagem = al_load_bitmap("cartas/21exatas.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
        }
        else if(curso == 2){
            imagem = al_load_bitmap("cartas/21humanas.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
        }
    }
    // Se for em muitas festas, seus amigos não vão te ajudar
    if (fluxo == 49){
            if(ContadorDeFestas >= 3 && PedirAjuda == true){
                imagem = al_load_bitmap("cartas/MtaFesta.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                if(atual != fluxo){
                    ProgTCC = ProgTCC + 15;
                    atual = fluxo;
                }
            }
            else if(PedirAjuda == true){
                imagem = al_load_bitmap("cartas/TccAjuda.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                if(atual != fluxo){
                    ProgTCC = ProgTCC + 40;
                    atual = fluxo;
                }
            }
            else if(PedirAjuda == false){
                imagem = al_load_bitmap("cartas/DesempregadoComTcc.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                if(atual != fluxo){
                    ProgTCC = ProgTCC + 40;
                    atual = fluxo;
                }
            }

    }
    // Comandos de texto
    if(fluxo == 16 || fluxo == 28 || fluxo == 25|| fluxo == 22|| fluxo == 41 || fluxo == 49){
        mostrar_status();
        if(fluxo > 41){
            al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 483, 120, ALLEGRO_ALIGN_LEFT, "TCC: %d", ProgTCC);
            al_draw_circle(590, 124, 3, al_map_rgb(0,0,0), 2);
            al_draw_circle(600, 135, 3, al_map_rgb(0, 0, 0), 2);
            al_draw_line(590, 135, 600, 124, al_map_rgb(0, 0, 0), 2);
        }
    }
    // Se for do time, entra de graça na festa
    if(fluxo == 31 && DoTime == true){
        dinheiro = dinheiro + 15;
    }

    if(fluxo >= 53){
            if(ProgTCC < 100){
                imagem = al_load_bitmap("cartas/consequencia_finais/SemTCC.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/2.7, ALTURA_TELA/1.05, ALLEGRO_ALIGN_LEFT, "Aperte ENTER para voltar ao menu");
                fluxo = 53;
            }

    }

    if(fluxo == 31){
            if(dog == true){
                al_play_sample(cachorro, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            else if(dog == false){
                al_play_sample(gato, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }

    }

}//Fim da função conseq_fluxo
/* ************************************************************************************************************************************************************************** */
int prova_semestral(){

    if(fluxo == 6 || fluxo == 12 || fluxo == 18 || fluxo == 26 || fluxo == 32 || fluxo == 38 || fluxo == 44 || fluxo == 51){
        if(curso == 1){
            if(fluxo == 6){
                imagem = al_load_bitmap("cartas/Exatas/prova1.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 12){
                imagem = al_load_bitmap("cartas/Exatas/prova2.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 18){
                imagem = al_load_bitmap("cartas/Exatas/prova3.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 26){
                imagem = al_load_bitmap("cartas/Exatas/prova4.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 32){
                imagem = al_load_bitmap("cartas/Exatas/prova5.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if (fluxo == 38){
                imagem = al_load_bitmap("cartas/Exatas/prova6.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if (fluxo == 44){
                imagem = al_load_bitmap("cartas/Exatas/prova7.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if (fluxo == 51){
                imagem = al_load_bitmap("cartas/Exatas/prova8.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }
        else{
            if(fluxo == 6){
                imagem = al_load_bitmap("cartas/Humanas/prova1.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 12){
                imagem = al_load_bitmap("cartas/Humanas/prova2.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 18){
                imagem = al_load_bitmap("cartas/Humanas/prova3.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 18){
                imagem = al_load_bitmap("cartas/Humanas/prova3.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 26){
                imagem = al_load_bitmap("cartas/Humanas/prova4.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }else if(fluxo == 32){
                imagem = al_load_bitmap("cartas/Humanas/prova5.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if(fluxo == 38){
                imagem = al_load_bitmap("cartas/Humanas/prova6.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if(fluxo == 44){
                imagem = al_load_bitmap("cartas/Humanas/prova7.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if(fluxo == 51){
                imagem = al_load_bitmap("cartas/Humanas/prova8.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }
    } // Fim do if de verificação de fluxo
}// Fim função prova_semestral
/* ************************************************************************************************************************************************************************** */
int ProvaDP(){
    if(DP > 0){
        // Avisar que vai começaras provas
        if(fluxo == 54){
            imagem = al_load_bitmap("cartas/ProvaDpStart.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), 555, 152, ALLEGRO_ALIGN_CENTER, "%d", DP);
        }
        // Prova da primeira DP
        if(fluxo == 55 && DP >= 1){
            if(curso == 1){
                imagem = al_load_bitmap("cartas/Exatas/DP/provaDP1.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if (curso == 2){
                imagem = al_load_bitmap("cartas/Humanas/DP/provaDP1.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }
        // Resultado da primeira prova
        if(fluxo == 56 && DP >= 1){
            if(aprovado == 0){
                imagem = al_load_bitmap("cartas/semestre-reprovado.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            } //Fim do if "aprovado == 0"
            else if(aprovado == 1){
                imagem = al_load_bitmap("cartas/ProvaAprovado.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }
        // Prova da segunda DP
        if(fluxo == 57 && DP == 2){
            if(curso == 1){
                imagem = al_load_bitmap("cartas/Exatas/DP/provaDP2.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
            else if (curso == 2){
                imagem = al_load_bitmap("cartas/Humanas/DP/provaDP2.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }
        // Resultado da segunda prova
        if(fluxo == 58 && DP == 2){
            if(aprovado == 0){
                imagem = al_load_bitmap("cartas/semestre-reprovado.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            } //Fim do if "aprovado == 0"
            else if(aprovado == 1){
                imagem = al_load_bitmap("cartas/ProvaAprovado.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
        }
    }
}
/* ************************************************************************************************************************************************************************** */
void jogando_fluxo(int tipo1, int valor1, int tipo2, int valor2, int consequencia){

    int auxFama = fama;
    int auxInteligencia = inteligencia;
    int auxDinheiro = dinheiro;
    int auxDP = DP;

    escolha(tipo1, valor1, tipo2, valor2, consequencia);
    fluxo++;
    if(fluxo != 31){
        al_play_sample(clique, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    imagem = al_load_bitmap(cartas[fluxo].texto);
    al_draw_bitmap(imagem, 0, 0, 0);

    mostrar_status();

    //animação(setas) dos atrubutoshttps://github.com/carolinevianab/AEscolhaDeUmUniversitario.git
    if(inteligencia > auxInteligencia){
        seta = al_load_bitmap("up.png");
        al_draw_bitmap(seta, 220, 5, 0);
    }else if(inteligencia < auxInteligencia){
        seta = al_load_bitmap("down.png");
        al_draw_bitmap(seta, 220, 5, 0);
    }

    if(fama > auxFama){
        seta = al_load_bitmap("up.png");
        al_draw_bitmap(seta, 120, 27.5, 0);
    }else if(fama < auxFama){
        seta = al_load_bitmap("down.png");
        al_draw_bitmap(seta, 120, 27.5, 0);
    }

    if(dinheiro > auxDinheiro){
        seta = al_load_bitmap("up.png");
        al_draw_bitmap(seta, 170, 45, 0);
    }else if(dinheiro < auxDinheiro){
        seta = al_load_bitmap("down.png");
        al_draw_bitmap(seta, 170, 45, 0);
    }

    if(fluxo > 41){
        al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 483, 120, ALLEGRO_ALIGN_LEFT, "TCC: %d", ProgTCC);
        al_draw_circle(590, 124, 3, al_map_rgb(0,0,0), 2);
        al_draw_circle(600, 135, 3, al_map_rgb(0, 0, 0), 2);
        al_draw_line(590, 135, 600, 124, al_map_rgb(0, 0, 0), 2);
    }

    prova_semestral();

    conseq_aprovacao();

    conseq_endgame();

    ending();

    ProvaDP();

    conseq_fluxo();

    //animação(seta) do atributo de dp
    //deve ficar depois de "conseq..." para não ser sobreposto com outra imagem
    if(DP > auxDP){
        seta = al_load_bitmap("upred.png");
        al_draw_bitmap(seta, 570, 96, 0);
    }else if(DP < auxDP){
        seta = al_load_bitmap("downgreen.png");
        al_draw_bitmap(seta, 570, 96, 0);
    }

    if(ProgTCC > 100){
        ProgTCC = 100;
    }

} // Fim da função jogando_fluxo
/* ************************************************************************************************************************************************************************** */
int ending(){
    if((fluxo >= 54 && DP==0) || (fluxo >= 57 && DP==1) || (fluxo >= 59 && DP==2)){
        if(TeoriaPodcast == true){
            if(curso == 1){// Teoria

                // Inteligência
                if(inteligencia > dinheiro && inteligencia > fama){
                    imagem = al_load_bitmap("cartas/endings/TeoriaInteligencia.bmp");
                    while(y>330){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 493, y-80,ALLEGRO_ALIGN_CENTER,"Depois de muita pesquisa,");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 488, y-65,ALLEGRO_ALIGN_CENTER,"voce conseguiu provar sua");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 500, y-50,ALLEGRO_ALIGN_CENTER,"teoria, o que mudou a");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 500, y-35,ALLEGRO_ALIGN_CENTER,"visao sobre algumas");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 500, y-20,ALLEGRO_ALIGN_CENTER,"coisas na sua area.");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 500, y-5,ALLEGRO_ALIGN_CENTER,"Voce ganhou diversos");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 500, y+10,ALLEGRO_ALIGN_CENTER,"premios por sua mente");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 500, y+25,ALLEGRO_ALIGN_CENTER,"brilhante!");
                        al_flip_display();
                        y = y - 0.5;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/UmaTeoriaInteligente.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }


                }

                // Fama
                else if(fama > inteligencia && fama > dinheiro){
                    imagem = al_load_bitmap("cartas/endings/TeoriaFama.bmp");
                    while(y>ALTURA_TELA/2){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y-45,ALLEGRO_ALIGN_LEFT,  "Sua teoria se tornou a mais");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y-30,ALLEGRO_ALIGN_LEFT,"discutida em seu meio, e");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y-15,ALLEGRO_ALIGN_LEFT,"voce foi chamado para");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y,ALLEGRO_ALIGN_LEFT,"fazer diversas entrevistas");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y+15,ALLEGRO_ALIGN_LEFT,"sobre ela. Cada dia que");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y+30,ALLEGRO_ALIGN_LEFT,"passava, mais e mais");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 10, y+45,ALLEGRO_ALIGN_LEFT,"conhecido voce se tornava!");
                        al_flip_display();
                        y = y - 0.5;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/FamosoTeorista.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }

                // Dinheiro
                else if(dinheiro > fama && dinheiro > inteligencia){
                        imagem = al_load_bitmap("cartas/endings/TeoriaDinheiro.bmp");
                        while(x < 960){
                            al_draw_bitmap(imagem, 0, 0, 0);
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), x-320, 180,ALLEGRO_ALIGN_RIGHT,"Voce investiu seu dinheiro e");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), x-320, 195,ALLEGRO_ALIGN_RIGHT,"financiou pesquisas avancadas");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), x-320, 210,ALLEGRO_ALIGN_RIGHT," que melhoraram nao apenas o");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), x-320, 225,ALLEGRO_ALIGN_RIGHT,"futuro da sua area, mas de");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), x-320, 240,ALLEGRO_ALIGN_RIGHT,"toda a humanidade.");
                            al_flip_display();
                            x = x + 1;
                        }
                        if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                            imagem = al_load_bitmap("cartas/endings/numbers/Pesquisador.bmp");
                            al_draw_bitmap(imagem, 0, 0, 0);
                        }
                }

            } // Fim do curso 1

            else if(curso == 2){// Podcast
                // Inteligência
                if(inteligencia > dinheiro && inteligencia > fama){
                    imagem = al_load_bitmap("cartas/endings/PodcastInteligencia.bmp");
                    while(x < 950){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), x-320, 15,ALLEGRO_ALIGN_RIGHT,"Seus podcasts informativos cresceram");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), x-320, 30,ALLEGRO_ALIGN_RIGHT,"pela universidade e se tornaram a fonte");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), x-320, 45,ALLEGRO_ALIGN_RIGHT,"numero 1 de pesquisas entre os estudantes,");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), x-320, 60,ALLEGRO_ALIGN_RIGHT,"sendo citado em diversos");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), x-320, 75,ALLEGRO_ALIGN_RIGHT,"TCCs, mestrados e");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), x-320, 90,ALLEGRO_ALIGN_RIGHT,"doutorados.");
                        al_flip_display();
                        x = x + 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/VozDaRazao.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }

                // Fama
                else if(fama > inteligencia && fama > dinheiro){
                    imagem = al_load_bitmap("cartas/endings/PodcastFama.bmp");
                    while(x > 0){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), x, 5,ALLEGRO_ALIGN_LEFT,"Seus podcasts ganharam tanta popularidade que toda a");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), x+47, 20,ALLEGRO_ALIGN_LEFT,"universidade comecou   a ouvir, ate mesmo de");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), x+80, 35,ALLEGRO_ALIGN_LEFT,"areas totalmente      diferentes da sua.");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), x, 440,ALLEGRO_ALIGN_LEFT,"Em pouco tempo, estavam em todas as plataformas para");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), x+320, 455,ALLEGRO_ALIGN_CENTER,"todo o mundo ouvir.");
                        al_flip_display();
                        x = x - 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/RodandoGlobo.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }

                // Dinheiro
                else if(dinheiro > fama && dinheiro > inteligencia){
                    imagem = al_load_bitmap("cartas/endings/PodcastDinheiro.bmp");
                    while(y > 1){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y,ALLEGRO_ALIGN_CENTER,"Voce investiu seu dinheiro e abriu uma gravadora e");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+15,ALLEGRO_ALIGN_CENTER,"publicadora de podcasts. Voce recebe muito");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+30,ALLEGRO_ALIGN_CENTER,"dinheiro de direitos autorais de pessoas do");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+45,ALLEGRO_ALIGN_CENTER,"mundo inteiro, que te procuram pela sua");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+60,ALLEGRO_ALIGN_CENTER,"qualidade e profissionalismo.");
                        al_flip_display();
                        y = y - 0.5;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/DiscoDeOuro.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }
            }
        } // Fim do if TeoriaPodcast

        if(JogoLivro == true){
            if(curso == 1){// Jogo

                // Inteligência
                if(inteligencia > dinheiro && inteligencia > fama){
                    imagem = al_load_bitmap("cartas/endings/JogoInteligencia.bmp");
                    while(y > 0){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+90,ALLEGRO_ALIGN_CENTER,"Seu jogo era tao");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+105,ALLEGRO_ALIGN_CENTER,"complexo e");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+120,ALLEGRO_ALIGN_CENTER,"completo de");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+135,ALLEGRO_ALIGN_CENTER,"informacao que");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+150,ALLEGRO_ALIGN_CENTER,"voce acabou");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+165,ALLEGRO_ALIGN_CENTER,"criando uma nova");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+180,ALLEGRO_ALIGN_CENTER,"engine promissora");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+195,ALLEGRO_ALIGN_CENTER,"com suporte");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+210,ALLEGRO_ALIGN_CENTER,"aprimorado e");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+225,ALLEGRO_ALIGN_CENTER,"funcoes mais");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+240,ALLEGRO_ALIGN_CENTER,"otimizadas que");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+255,ALLEGRO_ALIGN_CENTER,"em todas as");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 102, y+270,ALLEGRO_ALIGN_CENTER,"outras engines.");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 532, y+90,ALLEGRO_ALIGN_CENTER,"Ela se tornou a");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 532, y+105,ALLEGRO_ALIGN_CENTER,"mais usada pelos");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 532, y+120,ALLEGRO_ALIGN_CENTER,"gamemakers e o");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 532, y+135,ALLEGRO_ALIGN_CENTER,"centro das");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 532, y+150,ALLEGRO_ALIGN_CENTER,"atencoes da E3");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), 532, y+165,ALLEGRO_ALIGN_CENTER,"daquele ano.");
                        al_flip_display();
                        y = y - 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/UnivengineAEDU.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }

                // Fama
                else if(fama > inteligencia && fama > dinheiro){
                    imagem = al_load_bitmap("cartas/endings/JogoFama.bmp");
                        while(y > 150){
                            al_draw_bitmap(imagem, 0, 0, 0);
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 330, y,ALLEGRO_ALIGN_LEFT, "Seu jogo ficou");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 330, y+15,ALLEGRO_ALIGN_LEFT,"tao famoso pela");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 330, y+30,ALLEGRO_ALIGN_LEFT,"faculdade que voce");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 335, y+45,ALLEGRO_ALIGN_LEFT,"decidiu publica-lo");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 335, y+60,ALLEGRO_ALIGN_LEFT,"em diversos lugares.");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 335, y+75,ALLEGRO_ALIGN_LEFT,"Em pouco tempo, ja");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 335, y+90,ALLEGRO_ALIGN_LEFT,"havia mais de um");
                            al_draw_text(fontePixel,al_map_rgb(255,255,255), 335, y+105,ALLEGRO_ALIGN_LEFT,"milhao de downloads.");
                            al_flip_display();
                            y = y - 1;
                        }
                        if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/NovoKojima.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }

                // Dinheiro
                else if(dinheiro > fama && dinheiro > inteligencia){
                    imagem = al_load_bitmap("cartas/endings/JogoDinheiro.bmp");
                    while(y > 300){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), LARGURA_TELA/2, y+90,ALLEGRO_ALIGN_CENTER,"Voce investiu seu dinheiro na publicacao do seu jogo,");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), LARGURA_TELA/2, y+120,ALLEGRO_ALIGN_CENTER,"e em pouco tempo, abriu uma empresa para publicar");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), LARGURA_TELA/2, y+140,ALLEGRO_ALIGN_CENTER,"jogos indie, e assim divulga-los para o mundo.");
                        al_flip_display();
                        y = y - 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/EscolhaDeUmDesenvolvedor.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }

                }

            } // Fim de curso 1
            else if(curso == 2){// Livro

                // Inteligência
                if(inteligencia > dinheiro && inteligencia > fama){
                    imagem = al_load_bitmap("cartas/endings/LivroInteligencia.bmp");
                    while(y > 300){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixelGrande,al_map_rgb(0,0,0), 373, 200,ALLEGRO_ALIGN_LEFT,"Por");
                        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), 385, 225, ALLEGRO_ALIGN_LEFT, "%c.", nome[1]);
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+90,ALLEGRO_ALIGN_CENTER,"Voce se formou na faculdade e resolveu publicar o seu");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+105,ALLEGRO_ALIGN_CENTER,"TCC por uma editora bem conhecida na cidade.");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+120,ALLEGRO_ALIGN_CENTER,"Seu livro foi aclamado por todos da sua area,");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+135,ALLEGRO_ALIGN_CENTER,"crescendo por todo o territorio nacional e sendo");
                        al_draw_text(fontePixel,al_map_rgb(255,255,255), LARGURA_TELA/2, y+150,ALLEGRO_ALIGN_CENTER,"utilizado como referencia em diversos lugares.");
                        al_flip_display();
                        y = y - 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/Escritor.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                        if(sexo == 2){
                            al_draw_text(fontePixelGrande,al_map_rgb(0,0,0), 120, 330,ALLEGRO_ALIGN_CENTER,"a");


                        }
                        al_draw_text(fontePixelGrande,al_map_rgb(0,0,0), 373, 200,ALLEGRO_ALIGN_LEFT,"Por");
                        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), 385, 225, ALLEGRO_ALIGN_LEFT, "%c.", nome[1]);
                    }

                }

                // Fama
                else if(fama > inteligencia && fama > dinheiro){
                     imagem = al_load_bitmap("cartas/endings/LivroFamaa.bmp");
                    while(y > 70){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y,ALLEGRO_ALIGN_LEFT, "Antes mesmo de se");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+15,ALLEGRO_ALIGN_LEFT,"formar, voce ja");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+30,ALLEGRO_ALIGN_LEFT,"estava dando");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+45,ALLEGRO_ALIGN_LEFT,"entrevistas sobre");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+60,ALLEGRO_ALIGN_LEFT,"seus projetos.");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+75,ALLEGRO_ALIGN_LEFT,"Voce recebeu");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+90,ALLEGRO_ALIGN_LEFT,"diversas propostas");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+105,ALLEGRO_ALIGN_LEFT,"de emprego em");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+120,ALLEGRO_ALIGN_LEFT,"renomadas empresas,");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+135,ALLEGRO_ALIGN_LEFT,"e atualmente");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+150,ALLEGRO_ALIGN_LEFT,"trabalha numa das");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+165,ALLEGRO_ALIGN_LEFT,"melhores empresas");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 185, y+180,ALLEGRO_ALIGN_LEFT,"nacionais da area.");
                        al_flip_display();
                        y = y - 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/ConhecidoCompetente.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }

                // Dinheiro
                else if(dinheiro > fama && dinheiro > inteligencia){
                    imagem = al_load_bitmap("cartas/endings/LivroDinheiro.bmp");
                    while(y > ALTURA_TELA/2){
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y-90,ALLEGRO_ALIGN_LEFT,"Voce investiu");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y-75,ALLEGRO_ALIGN_LEFT,"seu dinheiro");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y-60,ALLEGRO_ALIGN_LEFT,"e abriu uma");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y-45,ALLEGRO_ALIGN_LEFT,"startup, que");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y-30,ALLEGRO_ALIGN_LEFT,"cresceu");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y-15,ALLEGRO_ALIGN_LEFT,"rapidamente.");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y,ALLEGRO_ALIGN_LEFT,"Com seu");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y+15,ALLEGRO_ALIGN_LEFT,"investimento");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y+30,ALLEGRO_ALIGN_LEFT,"e direcao,");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y+45,ALLEGRO_ALIGN_LEFT,"com certeza");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y+60,ALLEGRO_ALIGN_LEFT,"sera um");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y+75,ALLEGRO_ALIGN_LEFT,"negocio");
                        al_draw_text(fontePixel,al_map_rgb(0,0,0), 2, y+90,ALLEGRO_ALIGN_LEFT,"promissor.");
                        al_flip_display();
                        y = y - 1;
                    }
                    if((fluxo >= 55 && DP==0) || (fluxo >= 58 && DP==1) || (fluxo >= 60 && DP==2)){
                        imagem = al_load_bitmap("cartas/endings/numbers/Comecando.bmp");
                        al_draw_bitmap(imagem, 0, 0, 0);
                    }
                }
            }
        } // Fim do if JogoLivro
    }//Fim do if do fluxo
} // Fim da função ending
/* ************************************************************************************************************************************************************************** */
int comecarjogo(){
        imagem = al_load_bitmap(cartas[fluxo].texto);
        //toca o sinal
        al_play_sample(sinal, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

        //definição de dispositivos
        al_draw_bitmap(imagem, 0, 0, 0);

        mostrar_status();
        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);
        al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 530, 100, ALLEGRO_ALIGN_CENTER, "DPs: %d", DP);

        al_flip_display();

        while(!fim2){
            ALLEGRO_EVENT ev;
            al_wait_for_event(fila_eventos, &ev);

            //eventos de saida
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                fim = true;
                fim2 = true;
            }
            if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    fim = true;
                    fim2 = true;
                }
            }

            if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER){
                    if(inteligencia <= 0 || fama <= 0 || dinheiro <= 0 || inteligencia > 100 || fama > 100 || dinheiro > 100 || DP >= 3 || (fluxo == 53 && ProgTCC < 100)){
                        imagem = al_load_bitmap("telainicial.bmp");
                        fim2 = true;
                        resetar();
                    }
                    else if((fluxo >= 54 && DP==0) || (fluxo >= 57 && DP==1) || (fluxo >= 59 && DP==2)){
                        imagem = al_load_bitmap("telainicial.bmp");
                        fim2 = true;
                        resetar();
                    }
                }
            }

            //fluxo do jogo (LEFT / RIGHT CLICK)
            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && inteligencia > 0 && fama > 0 && dinheiro > 0
               && inteligencia <= 100 && fama <= 100 && dinheiro <= 100 && DP < 3){
                if(ev.mouse.x > LARGURA_TELA / 2){
                    jogando_fluxo(cartas[fluxo].esc2_tipo1, cartas[fluxo].valor1_esc2, cartas[fluxo].esc2_tipo2, cartas[fluxo].valor2_esc2, cartas[fluxo].consequenciaRight);
                }

                else if (ev.mouse.x < LARGURA_TELA / 2){
                    jogando_fluxo(cartas[fluxo].esc1_tipo1, cartas[fluxo].valor1_esc1, cartas[fluxo].esc1_tipo2, cartas[fluxo].valor2_esc1, cartas[fluxo].consequenciaLeft);
                }
            }

            al_flip_display();
        } // Fim do While
        return 0;
} // Fim da função comecarJogo
/* ************************************************************************************************************************************************************************** */
int creditos(){
    while(true){
            ALLEGRO_EVENT ev;
            al_wait_for_event(fila_eventos, &ev);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Feito por:");
            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 140, ALLEGRO_ALIGN_CENTRE, "Richard");
            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 180, ALLEGRO_ALIGN_CENTRE, "Caroline");
            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 220, ALLEGRO_ALIGN_CENTRE, "Guilherme");
            al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 260, ALLEGRO_ALIGN_CENTRE, "& Thiago");
            al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 425, ALLEGRO_ALIGN_CENTRE, "Irlanda");
            al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 450, ALLEGRO_ALIGN_CENTRE, "2019");
            al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 100, 460, ALLEGRO_ALIGN_CENTRE, "Ctrl para voltar");

            if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER){
                        break;
                    }
                    if(ev.keyboard.keycode == ALLEGRO_KEY_RCTRL || ev.keyboard.keycode == ALLEGRO_KEY_LCTRL){
                        return 3;
                    }
            }
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    fim = true;
                    break;

            }
            al_flip_display();
    } // Fim do While
} // Fim da função creditos
/* ************************************************************************************************************************************************************************** */
int thanos(){
    al_destroy_bitmap(imagem);
    al_destroy_bitmap(imagem_iniciar);
    al_destroy_bitmap(imagem_creditos);
    al_destroy_bitmap(imagem_sair);
    al_destroy_bitmap(imagem_tutorial);
    al_destroy_bitmap(prova);
    al_destroy_display(janela);
    al_destroy_font(fontePixelGrande);
    al_destroy_font(fontePixel);
    al_destroy_event_queue(fila_eventos);
    al_destroy_sample(sinal);
    al_destroy_sample(cachorro);
    al_destroy_sample(gato);
    al_destroy_sample(clique);
    al_destroy_sample(aplausos);
    al_destroy_audio_stream(musica);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_audio();
}
