//Sean Siders
//CS202
//Online Media System
//11/30/2020

/*
This abstraction manages an array of |Playlists|, which are linear linked lists. Each index of the array
represents a topic in a particular |Course|. This is a super-class of |Course|, as every course will have
a variety of topics and related media to present to the students.
 */

import java.io.FileNotFoundException;
import java.util.Scanner;

public class Channel extends Utils {

    //////////////// FIELDS

    //the array of |Playlists|
    Playlist [] array;

    //the number of |Playlists| in the array
    int playlistCount;

    //////////////// CONSTRUCTORS

    public Channel() {

        System.out.print("HOW MANY TOPICS DO YOU HAVE IN THIS COURSE?\nINTEGER INPUT >>> ");
        playlistCount = getInt();

        array = new Playlist[playlistCount];
        setupChannels();
    }

    public Channel(String filepath) throws FileNotFoundException {

        //load external data file with the filepath
        loadFile(filepath);

        //get a scanner object loaded with the fields for this channel
        Scanner fields = getFieldScanner("---");

        //read in from the scanner
        playlistCount = fields.nextInt();
        array = new Playlist[playlistCount];
        for (int i = 0; i < playlistCount; ++i) array[i] = new Playlist(fields.next());
    }

    //////////////// PUBLIC FUNCTIONS

    //display all |Playlists| in the array
    public void display() {

        for (int i = 0; i < playlistCount; ++i) {

            System.out.print("\n**************** TOPIC " + (i + 1) + " **************** \n\n");
            array[i].display();
        }
    }

    //display only the topic names of each playlist
    public void topicDisplay() {

        System.out.println();

        for (int i = 0; i < playlistCount; ++i) {
            System.out.print("TOPIC " + (i + 1) + " | ");
            array[i].displayName();
            System.out.println();
        }
    }

    //attempt to find a topic that has a title matching |topicName| (non-case sensitive)
    //return false if no topic match was found
    public boolean interactTopic(String topicName) {

        boolean matched = false;

        for (int i = 0; !matched && i < playlistCount; ++i) {

            if (array[i].nameCompare(topicName)) {

                matched = true;
                array[i].interact();
            }
        }

        return matched;
    }

    //insert |media| into the playlist at the specified |playlistIndex|
    public void insertAt(int playlistIndex, Media media) {

        if (0 > playlistIndex || playlistCount <= playlistIndex) array[0].insert(media);
        else array[playlistIndex].insert(media);
    }

    //insert |media| into a playlist that contains a name that matches |topicName|
    //false if no match was found
    public boolean insert(String topicName, Media media) {

        boolean success = false;
        for (int i = 0; !success && i < playlistCount; ++i) {

            //if a match is found, insert the item, and return true
            if (array[i].nameCompare(topicName)) {

                success = true;
                array[i].insert(media);
            }
        }

        return success;
    }

    //remove any media that have a title matching |removalKey|
    //only true if at least 1 removal occurs
    public boolean remove(String removalKey) {

        boolean removed = false;
        for (int i = 0; i < playlistCount; ++i) {

            if (array[i].remove(removalKey)) removed = true;
        }

        return removed;
    }

    //find the first media item that contains a title matching |retrievalKey|
    //return reference to the media object
    public Media retrieve(String retrievalKey) {

        //the media ref to return
        Media retrieved = null;

        //iterate through the array, attempting retrieval
        for (int i = 0; retrieved == null && i < playlistCount; ++i) retrieved = array[i].retrieve(retrievalKey);

        return retrieved;
    }

    //////////////// PRIVATE FUNCTIONS

    //go through the array of playlists, allocating and setting topic names for each one
    private void setupChannels() {

        for (int i = 0; i < playlistCount; ++i) {

            System.out.print("PLAYLIST " + (i + 1) + " / " + playlistCount + "\n");
            array[i] = new Playlist();
        }
    }
}
