import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * http://www.youtube.com/watch?v=iMo0bCSMAQ0
 * 
 * http://www.rubiksphotocube.com/fr/designer
 *
 */
public class RubikCubeCPC {
	static int no=0;
	public static void face(int xFrom, int xTo,Color xColor, int yFrom, int yTo, Color yColor,int z, Color zColor) throws IOException {
		BufferedImage image = new BufferedImage(99, 99, BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = image.createGraphics();

		if (xFrom<xTo) {
			if (yFrom<yTo) {
				for (int x=xFrom;x<=xTo; x++) {
					for (int y=yFrom; y<=yTo;y++) {
						hop(g2,x,y,z,xColor,yColor,zColor);
					}
				}
			} else {
				for (int x=xFrom;x<=xTo; x++) {
					for (int y=yFrom; y>=yTo;y--) {
						hop(g2,x,y,z,xColor,yColor,zColor);
					}
				}
			}
		} else {
			if (yFrom<yTo) {
				for (int x=xFrom;x>=xTo; x--) {
					for (int y=yFrom; y<=yTo;y++) {
						hop(g2,x,y,z,xColor,yColor,zColor);
					}
				}
			} else {
				for (int x=xFrom;x>=xTo; x--) {
					for (int y=yFrom; y>=yTo;y--) {
						hop(g2,x,y,z,xColor,yColor,zColor);
					}
				}
			}
		}
		File outputfile = new File("image"+no+".png");no++;
		ImageIO.write(image, "png", outputfile);
	}
	
	static int a,b=0;
	private static void hop(Graphics2D g2, int x, int y, int z, Color xColor, Color yColor, Color zColor) {
		// red : 255, 0 127 255
		int red = (xColor.getRed()*x)/2+(yColor.getRed()*y)/2+(zColor.getRed()*z)/2;
		int green = (xColor.getGreen()*x)/2+(yColor.getGreen()*y)/2+(zColor.getGreen()*z)/2;
		int blue = (xColor.getBlue()*x)/2+(yColor.getBlue()*y)/2+(zColor.getBlue()*z)/2;
		g2.setColor(new Color(red,green,blue));
		// 0-33 33-66 66-99
		System.out.println("x:"+x+" y:"+y);
		System.out.println("red:"+red+" green:"+green+" blue:"+blue);
		g2.fillRect(33*a, 33*b, 33*a+33, 33*b+33);
		a++;
		if (a==3) {
			a=0;
			b++;
		}
		if (b==3) {
			b=0;
		}
		
	}

	public static void main(String[] args) throws IOException {
		// noir
		//face(0,2,Color.BLUE,0,2,Color.RED,0,Color.GREEN);
		face(2,0,Color.BLUE,2,0,Color.RED,0,Color.GREEN);
		//face(0,2,Color.GREEN,0,2,Color.BLUE,0,Color.RED);
		face(2,0,Color.BLUE,0,2,Color.GREEN,0,Color.RED);
		
		// blanc
		//face(2,0,Color.RED,2,0,Color.BLUE,2,Color.GREEN);
		face(2,0,Color.BLUE,0,2,Color.RED,2,Color.GREEN);
		face(2,0,Color.BLUE,2,0,Color.GREEN,2,Color.RED);
		face(2,0,Color.GREEN,2,0,Color.RED,2,Color.BLUE);
		
		// noir
		face(0,2,Color.GREEN,2,0,Color.RED,0,Color.BLUE);
	}
}
