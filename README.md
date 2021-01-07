<h1 align='center'>README Generator in C</h1>
<p align='center'><a href='#description'>Description</a></p>
<p align='center'><a href='#installation'>Installation</a></p>
<p align='center'><a href='#usage'>Usage</a></p>
<p align='center'><a href='#license'>License</a></p>
<p align='center'><a href='#questions'>Questions</a></p>
<p align='center'><img src="screencapture.gif" alt="A screenshot of the project in VS code and a terminal window"></p>
<h2 align='center'>Description</h2>
<p align='center'>A command line interface tool for generating nice good looking README files</p>
<h2 align='center'>Installation</h2>
<p align='center'>Download it, compile the readmegen.c file, you need gcc or something equivalent, with gcc installed, open terminal and cd to the folder that contains readmegen.c and use the command</p>
<p align='center'><strong>gcc readmegen.c</strong></p>
<p align='center'>to compile it into an executable file named <strong>a.out</strong></p>
<p align='center'>A compiled and executable file named "generate" is also included in this repo if you don't want to compile it yourself</p>
<h2 align='center'>Usage</h2>
<p align='center'>Run the command</p>
<p align='center'><strong>./a.out</strong></p>
<p align='center'>Or, if you are using the file that comes with this repo, use the command</p>
<p align='center'><strong>./generate</strong></p>
<p align='center'>then answer the prompts with your app's information</p>
<p align='center'>If you supply one argument after a.out or generate, like</p>
<p align='center'><strong>./a.out MYREADME.md</strong></p>
<p align='center'>then it will write a file with that argument as its name</p>
<p align='center'>If no argument is provided, the default of <strong>README.md</strong> will be used</p>
<p align='center'>If you provide two arguments like so</p>
<p align='center'><strong>./a.out MYREADME.md orange</strong></p>
<p align='center'>or</p>
<p align='center'><strong>./generate NEWREADME.md #aaa111</strong></p>
<p align='center'>The second argument will be used as the color of the license badge. Color names or hexcodes can be used. If no second argument exists, license color will be based on the license used, and will default to a light blue if the license is not recognized. If the a second argument is given but the color is not valid, the color will default to green.</p>
<h2 align='center'>License</h2>
<p align='center'><img src='https://img.shields.io/badge/license-MIT-blue' alt='license'></img></p>
<h2 align='center'>Questions</h2>
<p align='center'>Any questions on this or other projects can be directed to thomasjfoydel@gmail.com</p>
<h2 align='center'>More Of My Projects</h2>
<p align='center'>Find more of my work on <a href='https://github.com/thomasfoydel'>my GitHub</a></p>
