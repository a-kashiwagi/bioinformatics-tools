//******************************************************************************
//                                                                            
// Title  :A two variable Gaussian Distribution by Gibbs Sampling             
// Program Name : gibbs.java                                                 
//                                                                            
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// e-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+---------+
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

import java.io.*;
import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;

//******************************************************************************
//                                                                            
// Title  : Gibbs sampling class                                              
// Class Name : gibbs                                                         
//                                                                            
// Detail : Initialize to jrand functions using init_gennrand() and srand()   
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+---------+
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

class gibbs extends JFrame {

	long TRIALS;

	double  a;
	double x1[] = new double[400];
	double x2[] = new double[400];

	gibbs(){

		TRIALS = 400;
		     a = 0.8;
	}

//******************************************************************************
//                                                                            
// Title  : Sampling method                                    
// Method Name : sampling                                                 
//                                                                           
// Detail : Sampling an uniform numbers from (-1) to (+1)                     
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Input  : void                                                              
//                                                                            
// Output : double : uniform numbers from (-1) to (+1)                        
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+----------
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

	double sampling(){

        	double num;
						// Get random numbers 0 to 1
        	num = Math.random();
						// Transfer -1 to +1
        	num = 2 * num - 1;

        	return num;
	}

//******************************************************************************
//                                                                            
// Title  : Random sampling from gauss distribution                                  
// Method Name : gauss                                                 
//                                                                           
// Detail : Random sampling from gauss distribution by Box-Muller Method                    
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Input  : double m : Number of mean                                                            
//        : double s : Number of standard deviation                             
//                                                                            
// Output : double : Random numbers from gauss distribution                   
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+----------
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

	double gauss( double m, double s ){

        	double z1;
        	double z2;
        	double y1;
        	double y2;
        	double rr;

		z1 = 0;
		z2 = 0;
		y1 = 0;
		y2 = 0;
		rr = 9;

		while( rr > 1 ){

        		z1 = sampling();
        		z2 = sampling();

        		rr = Math.pow(z1,2) + Math.pow(z2,2);
		}

        	y1 = z1 * Math.pow(( -2 * Math.log( rr ) ) / ( rr ),0.5);
        	// y2 = z2 * Math.pow(( -2 * Math.log( rr ) ) / ( rr ),0.5);

		return Math.sqrt(s) * y1 + m;
	}

//******************************************************************************
//                                                                            
// Title  : Draw Graph                                 
// Method Name : drawGraph                                                
//                                                                           
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+----------
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

	void drawGraph(){
						// Set window size
		this.setSize(400+20,400+50);
						// Add JPanel
		this.add(new GPanel(x1,x2,a), BorderLayout.CENTER);
						// Set close action
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

//******************************************************************************
//                                                                            
// Title  : Gibbs Sampling and Main function                                
// Method Name : main                                                
//                                                                           
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+----------
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

	public static void main(String[] args){

		gibbs g = new gibbs();
		int cnt;
						// Set init numbers
		g.x1[0] = 0;
		g.x2[0] = 0;
						// Gibbs Sampling loop
		for( cnt = 1; cnt < g.TRIALS; cnt++ ){

			System.out.printf(
				"%.12f,%.12f\n",
				g.x1[cnt-1],
				g.x2[cnt-1]
			);
						// Get p(x1|x2)
			g.x1[cnt] = g.gauss( g.a * g.x2[cnt-1], 1 );

						// Get p(x2|x1)
			g.x2[cnt] = g.gauss( g.a * g.x1[cnt]  , 1 );
		}
						// Draw graph
		g.drawGraph();
						// Show
		g.setVisible(true);
	}
}

//******************************************************************************
//                                                                            
// Title  : GPanel class                                              
// Class Name : GPanel                                                   
//                                                                            
// Detail : Draw graph 
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+---------+
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

class GPanel extends JPanel {

	double x1[] = new double[400];
	double x2[] = new double[400];
	double a;

//******************************************************************************
//                                                                            
// Title  : GPanel constructor                            
// Method Name : GPanel                                                 
//                                                                           
// Detail : Set data for graph                     
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Input  : double x1[] : x1 array                                                             
//        : double x2[] : x1 array                                                             
//        : double a    : Number of coef                                                            
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+----------
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

	GPanel(double x1_in[], double x2_in[], double a_in){

		for( int cnt = 0; cnt < 400; cnt++ ){

			x1[cnt] = x1_in[cnt];
			x2[cnt] = x2_in[cnt];
		}

		a = a_in;
	}

//******************************************************************************
//                                                                            
// Title  : Draw graph                       
// Method Name : paintComponent                                                
//                                                                           
// Date   : 2015.03.06                                                        
// Author : Akihiro Kashiwagi                                                 
// E-mail : a-kashiwagi@mippi-mail.com                                        
//                                                                            
// Input  : Graphics g : Graphics context                                                          
//                                                                            
// Replace ---------------------------------------------------------------------
//                                                                            
// Date   :                                                                   
// Author :                                                                   
// Deteil :                                                                   
//                                                                            
//-------+---------+---------+---------+---------+---------+---------+----------
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//******************************************************************************

	public void paintComponent(Graphics g){

						// Set super class
		super.paintComponent(g);
						// Get graphics context
		Graphics2D g2 = (Graphics2D)g;

						// Get window size
		int w = this.getWidth();
		int h = this.getHeight();
						// Set background color
		this.setBackground(Color.WHITE);

		for( int cnt = 1; cnt < 400; cnt++ ){
						// Draw x axsis sub line
			if( (cnt % 20) == 0 ){
				Line2D shape
					= new Line2D.Double( cnt, 0, cnt, 400 );
				g2.setPaint(new Color(200,200,200,255));
				g2.draw(shape);
			}
		}

		for( int cnt = 1; cnt < 400; cnt++ ){
						// Draw y axsis sub line
			if( (cnt % 20) == 0 ){
				Line2D shape
					= new Line2D.Double( 0, cnt, 400, cnt );
				g2.setPaint(new Color(200,200,200,255));
				g2.draw(shape);
			}
		}
						// Draw x axsis main line
		Line2D shape_y = new Line2D.Double( 200, 0, 200, 400 );
		g2.setPaint(new Color(128,128,128,255));
		g2.draw(shape_y);

						// Draw y axisi main line
		Line2D shape_x = new Line2D.Double( 0, 200, 400, 200 );
		g2.setPaint(new Color(128,128,128,255));
		g2.draw(shape_x);

						// Plot data
		for( int cnt = 0; cnt < 400; cnt++ ){
			Ellipse2D shape = new Ellipse2D.Double(
				200 + x1[cnt]*50 - 4,
				200 - x2[cnt]*50 - 4,
				8,8
			);
			g2.setPaint(new Color(0,0,255,255));
			g2.draw(shape);
		}
						// Print coef text
		g2.setPaint(new Color(0,0,0,255));
		g2.drawString(String.format("coef = %.2f",a),10,20);
	}
}
