//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
Node abstraction for the binary search tree of |Course| objects
 */

import java.io.FileNotFoundException;
import java.util.Scanner;

public class TreeNode {

    //////////////// FIELDS

    //the course in this node
    private Course course;

    //the left child
    private TreeNode left;

    //the right child
    private TreeNode right;

    //////////////// CONSTRUCTORS

    public TreeNode() {

        left = null;
        right = null;
    }

    //external data file source
    public TreeNode(String filepath) throws FileNotFoundException {

        left = null;
        right = null;

        course = new Course(filepath);
    }

    public TreeNode(Course source) {

        left = null;
        right = null;
        course = source;
    }

    //////////////// PUBLIC FUNCTIONS

    //get the left child
    public TreeNode left() {

        return left;
    }

    //get the right child
    public TreeNode right() {

        return right;
    }

    //get reference to the course this node manages
    public Course course() {

        return course;
    }

    //set left child
    public void setLeft(TreeNode left) {

        this.left = left;
    }

    //set right child
    public void setRight(TreeNode right) {

        this.right = right;
    }
}
