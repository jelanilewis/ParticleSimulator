/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package particle_simviewer;

import javafx.scene.paint.Color;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

/**
 *
 * @author jelanilyles
 */
public class Particle_SimViewer extends Application {
    
    
    
    static int numcells = 0, numsteps = 0, panewidth = 0, paneheight = 0;
    static Particle[][] particlesteps = new Particle[numsteps][numcells];
    static String text = "NOT READY";
    
    static void readin(String input) {
        
        
        try {
                   
            File file = new File(input);
            Scanner inFile = new Scanner(file);
            
            
            inFile.nextLine();
            String line = inFile.nextLine();
            String[] firstsplit = line.split(" ");
            
            numcells = Integer.parseInt(firstsplit[0]);
            numsteps = Integer.parseInt(firstsplit[1]);
            panewidth = Integer.parseInt(firstsplit[2]);
            paneheight = Integer.parseInt(firstsplit[3]);
            
                        for(int i = 0; i < numsteps; i++) {
                            for(int j = 0; j < numcells; j++) {
                                
                                line = inFile.nextLine();
                                String[] split = line.split(" ");
                
                                particlesteps[i][j].setPosx(Double.parseDouble(split[0]));
                                particlesteps[i][j].setPosy(Double.parseDouble(split[1]));
                                particlesteps[i][j].setVel(Double.parseDouble(split[2]));
                                particlesteps[i][j].setTheta(Double.parseDouble(split[3]));
                                particlesteps[i][j].setDr(Double.parseDouble(split[4]));
                                particlesteps[i][j].setPosx0(Double.parseDouble(split[5]));
                                particlesteps[i][j].setPosy0(Double.parseDouble(split[6]));
                                particlesteps[i][j].setDx(Double.parseDouble(split[7]));
                                particlesteps[i][j].setDy(Double.parseDouble(split[8]));
                                particlesteps[i][j].setDxbox(Double.parseDouble(split[9]));
                                particlesteps[i][j].setDybox(Double.parseDouble(split[10]));
                            }
                        }
                        
                        if(!inFile.hasNext()) {
                            text = "READY";
                        }
             
        } catch (FileNotFoundException ex) {
    
                    System.out.print("Unable to open/read file");
                    text = "Cannot read file.";       
        }
        
    }

    
            
    @Override
    public void start(Stage primaryStage) {
        
        
        
        
        
        BorderPane bp = new BorderPane();
        BorderPane bp2 = new BorderPane();
        Pane canvas = new Pane();
        canvas.setStyle("-fx-background-color: black;");
        canvas.setPrefSize(panewidth, paneheight);
        Node node = canvas;
       
        HBox hbox = new HBox();
        VBox vbox = new VBox();
        HBox hbox1 = new HBox();
        HBox hbox2 = new HBox();
        HBox top = new HBox();
        
        
        Node numcell = new Label("Number of Cells:");
        Node cells = new Label(Integer.toString(numcells));
        Node numstep = new Label("Step Number:");
        Node steps = new Label(Integer.toString(numsteps));
        Button btn = new Button("Start");
        Button btn1 = new Button("READ");
        Label ready = new Label();
        TextField filename = new TextField();
        
        filename.setEditable(true);
        bp2.setCenter(hbox);
        bp.setCenter(node);
        hbox.getChildren().addAll(vbox, btn, filename, btn1, ready);
        vbox.getChildren().addAll(hbox1, hbox2);
        hbox1.getChildren().addAll(numcell, cells);
        hbox2.getChildren().addAll(numstep, steps);
        
        
        
        btn.setOnAction(new EventHandler<ActionEvent>() {
            
            @Override
            public void handle(ActionEvent event) {
                
                
                
                
            
               
            }
        });
        
        btn1.setOnAction(new EventHandler<ActionEvent>() {
            
            public void handle(ActionEvent event) {
                
                
                readin(filename.getText());
                Cell[] cells = new Cell[numcells];
                Circle[] circles = new Circle[numcells];
                Rectangle[] rectangles = new Rectangle[numcells];
                
                for(int i = 0; i < numcells; i++) {
                    
                    Particle p = particlesteps[0][i];
                    
                    Cell c = new Cell();
                    
                    c.getHead().setCenterX(p.getPosx());
                    c.getHead().setCenterY(p.getPosy());
                    c.getHead().setStroke(Color.WHITE);
                    c.getTail().setX(p.getPosx());
                    c.getTail().setY(p.getPosy());
                    c.rotateTail(p.getTheta());
                    
                    circles[i] = c.getHead();
                    rectangles[i] = c.getTail();
                    
                    canvas.getChildren().add(c.getHead());
                    canvas.getChildren().add(c.getTail());
                }
                
                
                
                ready.setText(text);
            }
            
            
        });
        


        
       
        
        Scene scene = new Scene(hbox, 1000, 1000);
        
        primaryStage.setTitle("Cell Simulation");
        primaryStage.setScene(scene);
        primaryStage.show();
        
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        
        
        
        
        
        launch(args);
                
        
    }
    
}
