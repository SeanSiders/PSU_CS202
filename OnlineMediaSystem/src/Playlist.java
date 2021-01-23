//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
A Playlist contains any number of |Media| items from the media hierarchy. Dynamic binding is used
to call public functions from any of the sub-classes in the media hierarchy.
 */

public class Playlist extends Utils {

    //////////////// FIELDS

    //the front of the list
    private PlaylistNode head;

    //the name of this playlist, aka the topic name
    private String topicName;

    //the number of media items in the playlist
    private int playlistLength;

    //////////////// CONSTRUCTORS

    public Playlist() {

        head = null;
        playlistLength = 0;

        System.out.print("ENTER A TOPIC NAME FOR THIS PLAYLIST\n>>> ");
        topicName = getString();
    }

    public Playlist(String topicName) {

        head = null;
        playlistLength = 0;
        this.topicName = topicName;
    }

    //////////////// PUBLIC FUNCTIONS

    //// WRAPPER
    //display the topic name, and all media data in the playlist
    public void display() {

        System.out.print("TOPIC NAME | " + topicName + "\nPLAYLIST LENGTH | " + playlistLength + "\n");
        display(head, 1);
    }

    //display the |topicName|
    public void displayName() {

        System.out.print(topicName);
    }

    //true if |this.topicName| is a non-case sensitive match to |topicName|
    public boolean nameCompare(String topicName) {

        return this.topicName.equalsIgnoreCase(topicName);
    }

    //// WRAPPER
    //insert |media| at the end of the list
    public void insert(Media media) {

        head = insert(head, media);
        ++playlistLength;
    }

    //// WRAPPER
    //remove any media that have a title matching |removalKey|, case-sensitive
    //true if a match is found, resulting in a removal
    public boolean remove(String removalKey) {

        //record the original playlist length
        int originalLength = playlistLength;
        head = remove(head, removalKey);

        //only true if at least 1 removal occurs
        return playlistLength < originalLength;
    }

    //// WRAPPER
    //attempt to find a media item that has the matching title of |retrievalKey|
    //return reference to that media if a match is found
    public Media retrieve(String retrievalKey) {

        return retrieve(head, retrievalKey);
    }

    //// WRAPPER
    //interact with every media item in the playlist, in order
    public void interact() {

       interact(head);
    }

    //////////////// PRIVATE FUNCTIONS

    //// RECURSIVE
    //traverse with |head|, displaying all data, stopping at each item, user must hit enter to continue
    private void display(PlaylistNode head, int mediaIndex) {

        //end of the list
        if (head == null) return;

        //display the media item
        System.out.print("======== MEDIA ITEM " + mediaIndex + " / " + playlistLength + " ========\n");
        head.media().display();
        ++mediaIndex;

        //wait to continue with user input
        System.out.print("PRESS ENTER TO CONTINUE\n\n");
        getString();

        display(head.next(), mediaIndex);
    }

    //// RECURSIVE
    //traverse with |head|, inserting |media| at the end of the list
    private PlaylistNode insert(PlaylistNode head, Media media) {

        //end of the list, insert a new node
        if (head == null) {

            head = new PlaylistNode(media);
            return head;
        }

        //link up and return
        head.setNext(insert(head.next(), media));
        return head;
    }

    //// RECURSIVE
    //traverse with |head|, removing any nodes that have a match to |removalKey|
    private PlaylistNode remove(PlaylistNode head, String removalKey) {

        //end of the list
        if (head == null) return null;

        //if there is a match, traverse past, returning the first non-match to follow or null
        if (head.media().equals(removalKey)) {

            --playlistLength;
            return remove(head.next(), removalKey);
        }

        //link up and return
        head.setNext(remove(head.next(), removalKey));
        return head;
    }

    //// RECURSIVE
    //traverse with |head|, comparing |retrievalKey| to media items until a match is found
    //if a match is found return reference, otherwise return null
    private Media retrieve(PlaylistNode head, String retrievalKey) {

        //end of the list
        if (head == null) return null;

        //if a match is found
        if (head.media().nameCompare(retrievalKey)) return head.media();

        return retrieve(head.next(), retrievalKey);
    }

    //// RECURSIVE
    //traverse with |head|, interacting with each media item
    private void interact(PlaylistNode head) {

        if (head == null) return;
        head.media().interact();
        interact(head.next());
    }
}
