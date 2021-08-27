# Smart Teleprompter
For the midterm assignment, I built an automated LEGO SPIKE Prime system holding the WIO terminal so that the screen always faces the user as they move their face around while displaying scrolling text the user can read out loud. The facial recognition was achieve through implementing a OpenCV Haar Cascade Classifier on the Raspberry Pi camera and the teleprompter rotates to keep the face in the center of the camera using a proportional controller. Another proportional controller was implemented to control the font size of the scrolling WIO screen text by measuring the area of the identified face. Raspberry Pi commmunicated to the SPIKE Prime via UART serial connections and SPIKE then communicated to the WIO in the same way.

## Video
[Video of my teleprompter here!](https://youtu.be/RCjvoCnkEyo)

## Setup

#### Teleprompter
<img width="800" alt="Screen Shot 2021-08-27 at 5 24 21 PM" src="https://user-images.githubusercontent.com/49819466/131190104-7b9db6f4-6af0-4a16-b038-49462f52353d.png">

#### Teleprompter with Live Video Feed
<img width="1322" alt="Screen Shot 2021-08-27 at 5 22 55 PM" src="https://user-images.githubusercontent.com/49819466/131189989-b3252b0f-c7de-46c0-8a1a-193a5cceb650.png">
