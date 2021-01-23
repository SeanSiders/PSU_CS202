//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
This tree stores all courses that exist within a |University|. An instructor, admin or student can
access their courses and course content by retrieving the course in this tree.
 */

public class CourseTree extends Utils {

    //////////////// FIELDS

    //the root of the tree
    private TreeNode root;

    //the number of courses in the tree
    protected int courseCount;

    //////////////// CONSTRUCTORS

    CourseTree() {

        root = null;
        courseCount = 0;
    }

    //////////////// PUBLIC FUNCTIONS

    //display all course titles in the tree
    public boolean display() {

        if (root == null) return false;
        System.out.print("\nCOURSE COUNT | " + courseCount + "\n\n");
        display(root);

        return true;
    }

    //insert |toInsert| into the course tree
    public void insert(Course toInsert) {

        ++courseCount;
        root = insert(root, toInsert);
    }

    //attempt to retrieve a course with |retrievalKey|
    public Course retrieve(String retrievalKey) {

        return retrieve(root, retrievalKey);
    }

    //attempt to remove a course with |removalKey|
    //false if no match is found
    public boolean remove(String removalKey) {

        int originalCount = courseCount;
        root = remove(root, removalKey);

        return courseCount < originalCount;
    }

    //remove all nodes in the tree
    public void removeAll() {

        root = null;
        courseCount = 0;
    }

    //////////////// PRIVATE FUNCTIONS

    //traverse with |root| displaying all course titles in alphabetic order
    private void display(TreeNode root) {

        if (root == null) return;

        //traverse left
        display(root.left());

        //display course title
        root.course().displayName();
        System.out.println();

        //traverse right
        display(root.right());
    }

    //traverse the tree with |root| until a null root is found
    //allocate with |toInsert| and link up the tree
    private TreeNode insert(TreeNode root, Course toInsert) {

        if (root == null) {

            root = new TreeNode(toInsert);
            return root;
        }

        if (root.course().compareTitles(toInsert) < 0) root.setLeft(insert(root.left(), toInsert));
        else root.setRight(insert(root.right(), toInsert));

        return root;
    }

    //traverse the tree with |root|, attempting to retrieve a |Course| with a title that matches |retrievalKey|
    //return null if no match is found
    private Course retrieve(TreeNode root, String retrievalKey) {

        if (root == null) return null;

        int compareValue = root.course().compareTitles(retrievalKey);

        //a perfect match
        if (0 == compareValue) return root.course();

        //the |Course| to retrieve would be in the left subtree
        else if (0 > compareValue) return retrieve(root.left(), retrievalKey);

        //the |Course| to retrieve would be in the right subtree
        else return retrieve(root.right(), retrievalKey);
    }

    //traverse the tree with |root|, attempting to remove a |Course| with a title that matches |removalKey|
    private TreeNode remove(TreeNode root, String removalKey) {

        if (root == null) return null;

        int compareValue = root.course().compareTitles(removalKey);

        //a match was found, remove this node and find IOS
        if (0 == compareValue) {

            --courseCount;

            //if the node has a right subtree
            if (root.right() != null) {

                //hold onto right subtree
                TreeNode rightSubtree = root.right();
                TreeNode leftSubtree = root.left();

                //find the IOS
                root = getIOS(root.right());

                //remove the IOS from its original node
                root.setRight(removeIOS(rightSubtree));
                root.setLeft(leftSubtree);
            }

            //otherwise adopt the left subtree
            else root = root.left();

            return root;
        }

        //the |Course| to remove would be in the left subtree
        else if  (0 > compareValue) root.setLeft(remove(root.left(), removalKey));

        //the |Course| to remove would be in the right subtree
        else root.setRight(remove(root.right(), removalKey));

        return root;
    }

    //get the in-order successor in the right subtree of a node that will be removed
    private TreeNode getIOS(TreeNode root) {

        if (root.left() == null) return root;
        return getIOS(root.left());
    }

    //remove the IOS
    private TreeNode removeIOS(TreeNode root) {

        if (root.left() == null) return root.right();

        root.setLeft(removeIOS(root.left()));
        return root;
    }
}
