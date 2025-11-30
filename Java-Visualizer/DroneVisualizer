package dronevisualizerswing;

import javax.swing.*;
import javax.swing.Timer; 
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * A Swing-based visualizer for displaying drone swarm trajectories
 * produced by the C++ simulation. The visualizer reads a CSV file
 * (time, droneId, x, y, vx, vy), groups rows into frames, and animates
 * drone positions smoothly over time.
 *
 * Features:
 * - Scales the 0–100 world coordinates from the C++ simulation
 *   into the Swing panel coordinate system.
 * - Draws drones as colored circles.
 * - Displays time, frame index, and ID labels.
 * - 30 FPS animation using Swing Timer.
 */

public class DroneVisualizerSwing extends JPanel {

    // Inner Data Type

    /**
     * Represents a single simulation frame at a given time.
     * Each frame stores a mapping of droneId → 2D position.
     */
    
    private static class Frame {
        double time;
        Map<Integer, Point2D.Double> positions = new HashMap<>();
    }

    // Fields

    private final java.util.List<Frame> frames;
    private int frameIndex = 0;

    
    private static final double WORLD_SIZE = 100.0;

    // Colors assigned to drones based on ID
    
    private final Color[] droneColors = {
            Color.RED,
            Color.BLUE,
            Color.GREEN,
            Color.ORANGE,
            Color.MAGENTA,
            Color.CYAN
    };

    // Constructor

    /**
     * Creates the visualizer and starts the animation timer.
     *
     * @param frames A list of simulation frames loaded from CSV.
     */
    
    public DroneVisualizerSwing(java.util.List<Frame> frames) {
        this.frames = frames;
        setBackground(Color.BLACK);

        // animation timer: ~30 FPS
        int delayMs = 33;
        new Timer(delayMs, e -> {
            if (!frames.isEmpty()) {
                frameIndex++;
                if (frameIndex >= frames.size()) {
                    frameIndex = frames.size() - 1;  // stop at last frame (change to 0 to loop)
                }
                repaint();
            }
        }).start();
    }

    // Painting Logic

    /**
     * Paints the current frame (or a message if no frames loaded).
     */
    
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (frames.isEmpty()) {
            drawCenteredMessage(g, "No frames loaded");
            return;
        }

        Frame frame = frames.get(frameIndex);

        Graphics2D g2 = (Graphics2D) g.create();
        try {
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int width = getWidth();
            int height = getHeight();

            // Scale world 0..100 to panel size with margins
            
            double margin = 40;
            double usableWidth = width - 2 * margin;
            double usableHeight = height - 2 * margin;
            double scaleX = usableWidth / WORLD_SIZE;
            double scaleY = usableHeight / WORLD_SIZE;
            double scale = Math.min(scaleX, scaleY);

            // draw border
            
            g2.setColor(Color.DARK_GRAY);
            g2.drawRect((int) margin, (int) margin,
                        (int) (WORLD_SIZE * scale), (int) (WORLD_SIZE * scale));

            // Drones
            
            double droneRadius = 5.0 * scale / 2.0;

            for (Map.Entry<Integer, Point2D.Double> entry : frame.positions.entrySet()) {
                int id = entry.getKey();
                Point2D.Double pos = entry.getValue();

                double xWorld = pos.x;
                double yWorld = pos.y;

               
                double xScreen = margin + xWorld * scale;
                double yScreen = margin + (WORLD_SIZE - yWorld) * scale;

                Color color = droneColors[id % droneColors.length];
                g2.setColor(color);

                double r = droneRadius;
                Shape circle = new Ellipse2D.Double(xScreen - r, yScreen - r,
                                                    2 * r, 2 * r);
                g2.fill(circle);

                // Drone ID label
                
                g2.setColor(Color.WHITE);
                g2.drawString(Integer.toString(id),
                        (float) (xScreen + r + 2),
                        (float) (yScreen - r));
            }

           
            g2.setColor(Color.WHITE);
            g2.drawString(String.format("t = %.2f s   frame %d / %d",
                            frame.time, frameIndex + 1, frames.size()),
                    10, 20);

        } finally {
            g2.dispose();
        }
    }
    
    /**
     * Draws a message centered in the panel.
     *
     * @param g   Graphics context
     * @param msg Text to display
     */

    private void drawCenteredMessage(Graphics g, String msg) {
        g.setColor(Color.WHITE);
        FontMetrics fm = g.getFontMetrics();
        int x = (getWidth() - fm.stringWidth(msg)) / 2;
        int y = (getHeight() - fm.getHeight()) / 2 + fm.getAscent();
        g.drawString(msg, x, y);
    }

    // CSV loader
    
    /**
     * Loads simulation frames from a CSV file generated by the C++ simulator.
     * The CSV format must contain at least:
     *
     * <pre>
     * time, droneId, x, y, vx, vy
     * </pre>
     *
     * Rows with the same time value are grouped into one frame.
     *
     * @param path Path to the CSV file.
     * @return List of frames sorted by time.
     * @throws IOException if the file cannot be read.
     */

    public static java.util.List<Frame> loadFramesFromCsv(String path) throws IOException {
        java.util.List<Frame> frames = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            boolean first = true;

            
            Map<Double, Frame> frameByTime = new LinkedHashMap<>();

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;

                // Skip header
                if (first) {
                    first = false;
                    if (line.toLowerCase().startsWith("time")) {
                        continue;
                    }
                }

                String[] parts = line.split(",");
                if (parts.length < 6) continue;

                double time = Double.parseDouble(parts[0]);
                int droneId = Integer.parseInt(parts[1]);
                double x = Double.parseDouble(parts[2]);
                double y = Double.parseDouble(parts[3]);
                

                Frame frame = frameByTime.get(time);
                if (frame == null) {
                    frame = new Frame();
                    frame.time = time;
                    frameByTime.put(time, frame);
                }
                frame.positions.put(droneId, new Point2D.Double(x, y));
            }

            frames.addAll(frameByTime.values());
        }

        return frames;
    }

    // Main Method
    
    /**
     * Program entry point. Loads the CSV log file, initializes the visualizer,
     * and opens a Swing window showing the animated drone trajectory.
     *
     * @param args unused
     */

    public static void main(String[] args) {
        // Path to your C++ simulation log
        final String csvPath =
                "C:\\Users\\migue\\Documents\\DroneAnalyzer\\DroneAnalyzer\\simulation_log.csv";

        SwingUtilities.invokeLater(() -> {
            java.util.List<Frame> frames;
            try {
                frames = loadFramesFromCsv(csvPath);
            } catch (IOException e) {
                e.printStackTrace();
                JOptionPane.showMessageDialog(null,
                        "Failed to load " + csvPath + ":\n" + e.getMessage(),
                        "Error", JOptionPane.ERROR_MESSAGE);
                frames = Collections.emptyList();
            }

            JFrame frame = new JFrame("Drone Swarm Visualizer (Swing)");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            DroneVisualizerSwing panel = new DroneVisualizerSwing(frames);
            frame.setContentPane(panel);
            frame.setSize(800, 800);
            frame.setLocationRelativeTo(null); // center on screen
            frame.setVisible(true);
        });
    }
}
