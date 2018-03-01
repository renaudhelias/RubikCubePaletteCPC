import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
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
	
	static int no = 0;

	public static void face(int xFrom, int xTo, Color xColor, int yFrom, int yTo, Color yColor, int z, Color zColor)
			throws IOException {
		face(xFrom, xTo, xColor, yFrom, yTo, yColor, z, zColor,false);
	}
	public static void face(int xFrom, int xTo, Color xColor, int yFrom, int yTo, Color yColor, int z, Color zColor, boolean isHard)
			throws IOException {
		BufferedImage image = new BufferedImage(999, 999, BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = image.createGraphics();

		if (xFrom < xTo) {
			if (yFrom < yTo) {
				for (int x = xFrom; x <= xTo; x++) {
					for (int y = yFrom; y <= yTo; y++) {
						hop(g2, x, y, z, xColor, yColor, zColor,isHard);
					}
				}
			} else {
				for (int x = xFrom; x <= xTo; x++) {
					for (int y = yFrom; y >= yTo; y--) {
						hop(g2, x, y, z, xColor, yColor, zColor,isHard);
					}
				}
			}
		} else {
			if (yFrom < yTo) {
				for (int x = xFrom; x >= xTo; x--) {
					for (int y = yFrom; y <= yTo; y++) {
						hop(g2, x, y, z, xColor, yColor, zColor,isHard);
					}
				}
			} else {
				for (int x = xFrom; x >= xTo; x--) {
					for (int y = yFrom; y >= yTo; y--) {
						hop(g2, x, y, z, xColor, yColor, zColor,isHard);
					}
				}
			}
		}
		File outputfile;
		if (isHard) {
			outputfile= new File("hard_image" + no + "ComicNumbers.png");
		} else {
			outputfile = new File("image" + no + "ComicNumbers.png");
		}
		no++;
		ImageIO.write(image, "png", outputfile);
	}

	static int a, b = 0;
	static int palette[][][];
	static int hard_palette[][][];

	/**
	 * 
	 * @param red
	 *            0 127 255
	 * @param green
	 *            0 127 255
	 * @param blue
	 *            0 127 255
	 * @return
	 */
	static int palette(int red, int green, int blue,boolean isHard) {
		int r = red / 127;
		int g = green / 127;
		int b = blue / 127;
		if (isHard) {
			return hard_palette[r][g][b];
		} else {
			return palette[r][g][b];
		}
	}

	private static void hop(Graphics2D g2, int x, int y, int z, Color xColor, Color yColor, Color zColor,boolean isHard) {
		// red : 255, 0 127 255
		int red = (xColor.getRed() * x) / 2 + (yColor.getRed() * y) / 2 + (zColor.getRed() * z) / 2;
		int green = (xColor.getGreen() * x) / 2 + (yColor.getGreen() * y) / 2 + (zColor.getGreen() * z) / 2;
		int blue = (xColor.getBlue() * x) / 2 + (yColor.getBlue() * y) / 2 + (zColor.getBlue() * z) / 2;
		g2.setColor(new Color(red, green, blue));
		// 0-333 333-666 666-999
		System.out.println("x:" + x + " y:" + y);
		System.out.println("red:" + red + " green:" + green + " blue:" + blue);
		g2.fillRect(333 * a, 333 * b, 333 * a + 333, 333 * b + 333);
		if (isHard) {
			if (red==255 && green==255 && blue==255) {
				g2.setColor(new Color(0, 0, 0));				
			} else {
				g2.setColor(new Color(255, 255, 255));
			}
		} else {
			g2.setColor(new Color(0, 0, 0));
		}
		g2.setFont(new Font("Comics", Font.PLAIN, 222));
		String value;
		if (isHard) {
			value = Integer.toHexString(palette(red,green,blue,isHard)).toUpperCase();
		} else {
			value = String.valueOf(palette(red,green,blue,isHard));
		}
		Rectangle2D bounds = g2.getFontMetrics().getStringBounds(value, g2);
		g2.drawString(value, (int) (333 * a + (333 - bounds.getWidth()) / 2), (int) (333 * b + 333 - 99));// +
																										// 333-));
		a++;
		if (a == 3) {
			a = 0;
			b++;
		}
		if (b == 3) {
			b = 0;
		}

	}

	public static void main(String[] args) throws IOException {
		palette = new int[3][3][3];

		palette[0][0][0] = 0;
		palette[0][0][1] = 1;
		palette[0][0][2] = 2;
		palette[0][1][0] = 9;
		palette[0][1][1] = 10;
		palette[0][1][2] = 11;
		palette[0][2][0] = 18;
		palette[0][2][1] = 19;
		palette[0][2][2] = 20;

		palette[1][0][0] = 3;
		palette[1][0][1] = 4;
		palette[1][0][2] = 5;
		palette[1][1][0] = 12;
		palette[1][1][1] = 13;
		palette[1][1][2] = 14;
		palette[1][2][0] = 21;
		palette[1][2][1] = 22;
		palette[1][2][2] = 23;

		palette[2][0][0] = 6;
		palette[2][0][1] = 7;
		palette[2][0][2] = 8;
		palette[2][1][0] = 15;
		palette[2][1][1] = 16;
		palette[2][1][2] = 17;
		palette[2][2][0] = 24;
		palette[2][2][1] = 25;
		palette[2][2][2] = 26;
		
		hard_palette = new int[3][3][3];

		hard_palette[0][0][0] = 0x54; // 0
		hard_palette[0][0][1] = 0x44; // 1
		hard_palette[0][0][2] = 0x55; // 2
		hard_palette[0][1][0] = 0x56; // 9
		hard_palette[0][1][1] = 0x46; // 10
		hard_palette[0][1][2] = 0x57; // 11
		hard_palette[0][2][0] = 0x52; // 18
		hard_palette[0][2][1] = 0x42; // 19
		hard_palette[0][2][2] = 0x53; // 20

		hard_palette[1][0][0] = 0x5C; // 3
		hard_palette[1][0][1] = 0x58; // 4
		hard_palette[1][0][2] = 0x5D; // 5
		hard_palette[1][1][0] = 0x5E; // 12
		hard_palette[1][1][1] = 0x40; // 13
		hard_palette[1][1][2] = 0x5F; // 14
		hard_palette[1][2][0] = 0x5A; // 21
		hard_palette[1][2][1] = 0x59; // 22
		hard_palette[1][2][2] = 0x5B; // 23

		hard_palette[2][0][0] = 0x4C; // 6
		hard_palette[2][0][1] = 0x45; // 7
		hard_palette[2][0][2] = 0x4D; // 8
		hard_palette[2][1][0] = 0x4E; // 15
		hard_palette[2][1][1] = 0x47; // 16
		hard_palette[2][1][2] = 0x4F; // 17
		hard_palette[2][2][0] = 0x4A; // 24
		hard_palette[2][2][1] = 0x43; // 25
		hard_palette[2][2][2] = 0x4B; // 26
		
		//palette
		// noir
		face(2, 0, Color.BLUE, 2, 0, Color.RED, 0, Color.GREEN);
		face(2, 0, Color.BLUE, 0, 2, Color.GREEN, 0, Color.RED);

		// blanc
		face(2, 0, Color.BLUE, 0, 2, Color.RED, 2, Color.GREEN);
		face(2, 0, Color.BLUE, 2, 0, Color.GREEN, 2, Color.RED);
		face(2, 0, Color.GREEN, 2, 0, Color.RED, 2, Color.BLUE);

		// noir
		face(0, 2, Color.GREEN, 2, 0, Color.RED, 0, Color.BLUE);

		no=0;
		//hard_palette
		// noir
		face(2, 0, Color.BLUE, 2, 0, Color.RED, 0, Color.GREEN,true);
		face(2, 0, Color.BLUE, 0, 2, Color.GREEN, 0, Color.RED,true);

		// blanc
		face(2, 0, Color.BLUE, 0, 2, Color.RED, 2, Color.GREEN,true);
		face(2, 0, Color.BLUE, 2, 0, Color.GREEN, 2, Color.RED,true);
		face(2, 0, Color.GREEN, 2, 0, Color.RED, 2, Color.BLUE,true);

		// noir
		face(0, 2, Color.GREEN, 2, 0, Color.RED, 0, Color.BLUE,true);

	}
}
