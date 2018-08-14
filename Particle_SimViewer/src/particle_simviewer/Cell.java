/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package particle_simviewer;

import java.awt.Color;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.transform.Rotate;

/**
 *
 * @author jelanilyles
 */
public class Cell {
    
    private Circle head;
    private Rectangle tail;
    
    public Cell() {
        head.setRadius(10);
        tail.setWidth(20);
        tail.setHeight(3);
    }
    
    public Cell(double x, double y, double theta) {
        
        
        head.setRadius(10);
        head.setCenterX(x);
        head.setCenterY(y);
        tail.setX(x);
        tail.setY(y);
        tail.setWidth(20);
        tail.setHeight(3);
        rotateTail(theta);
        
    }
    
    public void rotateTail(double theta) {
        Rotate rotate = new Rotate();
        rotate.setPivotX(this.getTail().getX()); //Pivot X Top-Left corner
        rotate.setPivotY(this.getTail().getY()); //Pivot Y
        rotate.setAngle(theta);
        
        this.getTail().getTransforms().add(rotate);
    }
    
    public void drawCell(Pane pane) {
        
        
    }

    /**
     * @return the head
     */
    public Circle getHead() {
        return head;
    }

    /**
     * @param head the head to set
     */
    public void setHead(Circle head) {
        this.head = head;
    }

    /**
     * @return the tail
     */
    public Rectangle getTail() {
        return tail;
    }

    /**
     * @param tail the tail to set
     */
    public void setTail(Rectangle tail) {
        this.tail = tail;
    }
    
    
    
}
