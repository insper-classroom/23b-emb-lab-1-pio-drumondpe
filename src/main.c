/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

/*
// PLACA ###################################################
#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        ID_PIOC  		       // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED
// #########################################################
*/

// OLED1
#define LED1			PIOA
#define LED1_ID			ID_PIOA 
#define LED1_IDX		0
#define LED1_IDX_MASK	(1 << LED1_IDX)

// OLED2
#define LED2			PIOC	
#define LED2_ID			ID_PIOC
#define LED2_IDX		30
#define LED2_IDX_MASK	(1 << LED2_IDX)

// OLED3
#define LED3			PIOB
#define	LED3_ID			ID_PIOB
#define LED3_IDX		2
#define LED3_IDX_MASK	(1 << LED3_IDX)

/*
// Configuracoes do botao #####################################
#define BUT_PIO			PIOA	
#define BUT_PIO_ID		ID_PIOA // 10
#define BUT_PIO_IDX		11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX) // esse já está pronto.
// ############################################################
*/

// BUTTON1
#define BUTTON1			PIOD
#define BUTTON1_ID		ID_PIOD
#define BUTTON1_IDX		28
#define BUTTON1_IDX_MASK (1u << BUTTON1_IDX)

// BUTTON2 - PC31
#define BUTTON2			PIOC
#define BUTTON2_ID		ID_PIOC
#define BUTTON2_IDX		31
#define BUTTON2_IDX_MASK (1u << BUTTON2_IDX)

// BUTTON3 - PA19
#define BUTTON3			PIOA
#define BUTTON3_ID		ID_PIOA
#define BUTTON3_IDX		19
#define BUTTON3_IDX_MASK (1u << BUTTON3_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void)
{
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado para que possamos controlar o LED.
	//pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(LED1_ID);
	pmc_enable_periph_clk(LED2_ID);
	pmc_enable_periph_clk(LED3_ID);
	
	//Inicializa PC8 como saída
	//pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0); // A função recebe como parâmetro o PIO e a máscara LED_PIO_IDX_MASK (que representa qual pino do PIO será configurado
	pio_set_output(LED1, LED1_IDX_MASK, 0, 0, 0);
	pio_set_output(LED2, LED2_IDX_MASK, 0, 0, 0);
	pio_set_output(LED3, LED3_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	//pmc_enable_periph_clk(BUT_PIO_ID);
	pmc_enable_periph_clk(BUTTON1_ID);
	pmc_enable_periph_clk(BUTTON2_ID);
	pmc_enable_periph_clk(BUTTON3_ID);
	
	// configura pino ligado ao botão como entrada com um pull-up.
	//pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_DEFAULT);
	//pio_pull_up(BUT_PIO, BUT_PIO_IDX_MASK, 1);
	
	pio_set_input(BUTTON1, BUTTON1_IDX_MASK, PIO_DEFAULT);
	pio_pull_up(BUTTON1, BUTTON1_IDX_MASK, 1);
	
	pio_set_input(BUTTON2, BUTTON2_IDX_MASK, PIO_DEFAULT);
	pio_pull_up(BUTTON2, BUTTON2_IDX_MASK, 1);
	
	pio_set_input(BUTTON3, BUTTON3_IDX_MASK, PIO_DEFAULT);
	pio_pull_up(BUTTON3, BUTTON3_IDX_MASK, 1);
	
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void) {
	// inicializa sistema e IOs
	init();

	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1)
	{
		/*
		pio_set(LED_PIO, LED_PIO_IDX_MASK);      // Coloca 1 no pino LED (desliga)
		delay_ms(1000);                        // Delay por software de 200 ms
		pio_clear(LED_PIO, LED_PIO_IDX_MASK);    // Coloca 0 no pino do LED (liga)
		delay_ms(3000);                        // Delay por software de 200 ms
		*/
		
		/*
		if (pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 0) { // Check if button is pressed
			for (int i = 0; i < 5; i++) {
				pio_clear(LED_PIO, LED_PIO_IDX_MASK); // Turn on LED
				delay_ms(500);
				pio_set(LED_PIO, LED_PIO_IDX_MASK);   // Turn off LED
				delay_ms(500);
			}
			// Wait for button to be released
			while (pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 0) {
				// Do nothing, just wait for button release
			}
		}
		*/
		// BUTTON1 E LED1
		if (pio_get(BUTTON1, PIO_INPUT, BUTTON1_IDX_MASK) == 0) { // Check if button is pressed
			for (int i = 0; i < 5; i++) {
				pio_clear(LED1, LED1_IDX_MASK); // Turn on LED
				delay_ms(500);
				pio_set(LED1, LED1_IDX_MASK);   // Turn off LED
				delay_ms(500);
			}
			// Wait for button to be released
			while (pio_get(BUTTON1, PIO_INPUT, BUTTON1_IDX_MASK) == 0) {
				// Do nothing, just wait for button release
			}	
		}
		
		// BUTTON2 E LED2
		if (pio_get(BUTTON2, PIO_INPUT, BUTTON2_IDX_MASK) == 0) { // Check if button is pressed
			for (int i = 0; i < 5; i++) {
				pio_clear(LED2, LED2_IDX_MASK); // Turn on LED
				delay_ms(500);
				pio_set(LED2, LED2_IDX_MASK);   // Turn off LED
				delay_ms(500);
			}
			// Wait for button to be released
			while (pio_get(BUTTON2, PIO_INPUT, BUTTON2_IDX_MASK) == 0) {
				// Do nothing, just wait for button release
			}
		}
		
		// BUTTON3 E LED3
		if (pio_get(BUTTON3, PIO_INPUT, BUTTON3_IDX_MASK) == 0) { // Check if button is pressed
			for (int i = 0; i < 5; i++) {
				pio_clear(LED3, LED3_IDX_MASK); // Turn on LED
				delay_ms(500);
				pio_set(LED3, LED3_IDX_MASK);   // Turn off LED
				delay_ms(500);
			}
			// Wait for button to be released
			while (pio_get(BUTTON3, PIO_INPUT, BUTTON3_IDX_MASK) == 0) {
				// Do nothing, just wait for button release
			}
		}
		
		 
	
	}

	return 0;
}