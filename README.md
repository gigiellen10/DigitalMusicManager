# DigitalMusicManager

Program implemented with a dynamically-allocated doubly linked list; supports linked list traversal, manipulation, sorting, editing, deletions, insertions and link modifications. Each song record is encapsulated in a Record struct
containing: 
Artist – C string
Album title – C string
Song title – C string
Genre – C string
Song length - a struct Duration type consisting of seconds and minutes, both integers
Number times played – an integer
Rating – an integer (1 – 5)

Three test functions implemented in testing.c for shuffle(), delete() and insert() functions.
These test functions are self-sufficient and will execute after the main menu loop is exited by the user
entering (11) exit. 

Text-based "digital music manager" that allows a user to apply the following commands: 
(all user input is validated)
(1) load 
Reads records from musicPlaylist.csv file, parses the data and stores data into a 
doubly dynamically linked list. Command overwrites any existing data in linked list with
new data from the file.

(2) store 
Writes all records currently contained in the list to the "musicPlaylist.csv" file. Command 
overwrites any data already contained in the file.

(3) display 
Allows the user to choose to display records matching an artist, or display all records in the 
"playlist." Command displays corresponding data based on user selection.

(4) insert 
Inserts a new record into the front of the playlist. Prompts the user for the required information 
for this record.

(5) delete 
Prompts the user to enter a song to delete from the playlist. Searches the playlist and finds the first
instantiation of the string entered. The corresponding record is deleted and the links are modified 
accordingly to this deletion.

(6) edit 
Searches for a specific artist and finds all instances of records with the artist name. If more than one
instantiation, prompts user to select which record to edit. Allows the user to modify all fields in the 
selected record.

(7) sort 
Implements a bubble-sort algorithm to the doubly linked list. Allows the user to sort based on album title (A-Z), 
artist name (A-Z), rating (ascending) and times played (descending).

(8) rate
Allows the user to search for a song title and modify the rating of that record.

(9) play 
Allows user to select a song, searches for that song, and begins "playing" that song from the first instantiation of
the song until the end of the playlist is reached. "Playing" consists of displaying all fields of a Record to the screen
for a short time.

(10) shuffle 
Generates a random order to "play" the songs in the playlist. Command will "play" those songs and display the
order in which they were played.

(11) exit
Stores all records currently contained in the playlist in "musicPlaylist.csv," overwriting any previous data existing
in the file. Closes the file and exits the program.
