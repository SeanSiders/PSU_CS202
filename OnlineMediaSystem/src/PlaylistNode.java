//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
Node abstraction for the |Playlist| class. Underlying data is a |Media| reference, allowing for
dynamic binding to occur.
 */

public class PlaylistNode {

    //////////////// FIELDS

    //the media item this node contains
    //this can be any item in the media hierarchy
    private Media media;

    //next node in the list
    private PlaylistNode next;

    //////////////// CONSTRUCTORS

    public PlaylistNode() {

        next = null;
    }

    public PlaylistNode(Media media) {

        this.media = media;
        next = null;
    }

    //////////////// PUBLIC FUNCTIONS

    //get reference to the media item
    public Media media() {

        return media;
    }

    //get the next node in the list
    public PlaylistNode next() {

        return next;
    }

    //set the next node in the list
    public void setNext(PlaylistNode next) {

        this.next = next;
    }
}
