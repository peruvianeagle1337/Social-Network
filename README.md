# Moodboards-Social-Network
 Social Network for Advanced Programming Course 

    *QT Studio Application*

 
Features: 

Run Mainwindow.cpp to Launch the Log-In Screen 
 
  Requires a valid Username (drawn from users.txt)


Uses Vectors to Store Each User's Friends

Finds a list of Most Relevant Friend Suggestions (click to add)

Text Posts: Users can write posts on their own and on each other's profiles!


Additional Features: 
• Profile Pictures for each user
• Biographies for each user
• Like feature for Posts
• A Moodboard where users can pin stickers (visible to friends)

1. Profile Picture Feature

Class & Field Modifications
User Class:
 • Add field: profilePicture: Image (or URL string)
 • Methods to modify/add:
  – setProfilePicture(pic: Image): void – Sets or updates the profile picture.
  – getProfilePicture(): Image – Returns the current profile picture.

UI Updates
Update the profile view to include a dedicated image widget (e.g., top left corner).
Provide an “Upload Picture” button adjacent to the widget.
Sketch: A box showing the current profile image with an “Upload” icon next to it.

Slots & Signals
Slot: onProfilePictureUpload() – Triggered when the user clicks the “Upload Picture” button. Opens a file dialog and updates the profile picture field upon selection.
Signal: profilePictureChanged – Emitted after successful upload to refresh all UI views where the profile picture is displayed.

2. Biography Feature

Class & Field Modifications
User Class:
 • Add field: biography: String
 • Methods:
  – setBiography(bio: String): void – Updates the user’s biography.
  – getBiography(): String – Retrieves the current biography text.

UI Updates
In the profile page, add a text area labeled “Biography.”
Provide an “Edit” button to allow in-place modifications.
Sketch: A multi-line text box under the profile picture, with a pencil icon for editing.

Slots & Signals
Slot: onBiographyUpdate() – Invoked when the user saves changes from the text area. Validates and commits changes to the biography field.
Signal: biographyUpdated – Emitted to notify other components (e.g., friend views) that the biography has been updated.

3. Likes for Posts

Class & Field Modifications
Post Class:
 • Add field: likes: List<User> 	(tracking the users)
 • Methods to add/modify:
  – addLike(user: User): void – Adds the user to the likes list. Checks for duplicate likes before adding.
  – removeLike(user: User): void – Removes the user if they decide to “unlike.”
  – getLikeCount(): int – Returns the total number of likes.

UI Updates
Update each post view to include a “Like” icon (e.g., a heart or thumbs-up) along with a visible count of likes.
Clicking the icon triggers like/unlike behavior.

Slots & Signals
Slot: onLikePost() – Connected to the “Like” icon’s click event; it calls addLike or removeLike accordingly.
Signal: likeUpdated – Emitted after a like/unlike operation, prompting the UI to refresh the like count.

4. Experimental Feature: Moodboard
Class Design
Moodboard Class:
 • Field: stickers: List<Sticker>
 • Sticker Class:
  – Fields: image: Image, position: (x, y), timestamp: DateTime
 • Methods:
  – addSticker(sticker: Sticker): void – Adds a new sticker to the moodboard.
  – removeSticker(stickerID: int): void – Removes a sticker based on its identifier.
  – getStickers(): List<Sticker> – Returns all stickers currently pinned.

UI Updates
Add a dedicated “Moodboard” section on the user’s profile.
Layout: A grid or canvas where stickers appear at designated positions.
Allow friends to drag-and-drop stickers onto the moodboard.

Slots & Signals
Slot: onStickerPinned() – Triggered when a user pins a sticker. Validates the sticker and updates the moodboard data.
Signal: stickerAdded – Emitted to update all friend views of the moodboard.
