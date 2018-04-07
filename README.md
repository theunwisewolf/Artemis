# Artemis
Artemis is a 2D vector graphics library that I & a few friends built. It is a step in modern graphics development to ease the difficulties faced by all kinds of game programmers. It is similar to SVG except that I have chosen simplicty over complexity. It involves some very basic renderable primitives inspired from Processing(p5.js). 

It allows you to separate out your game logic from your rendering part. You write your renderable descriptions in a separate file and then import it using Artemis' parser into your game and render them. This has two advantages:
1. You are able to write & change your renderables without doing any modification to your existing game code.
2. Designers and Programmers can now work separtely!

Alright, enough talking! Let's get into some code now.

## Repository Details
Artemis comes with a parser and an example Breakout Game which should give you enough details on how to use Artemis! 

Plus, I also included some examples inside the tests folder, like the ```us_map.aml"``` which shows the usage of the ```<polygon>``` tag.

## Running Artemis Breakout (Example Project)
Clone the repository onto your machine.
Launch the solution, select your build configuration: x86 or x64 & set ArtemisBreakout as your startup Project.
Run & see for yourself!

## Usage

Using Artemis is pretty simple. You first create your definitions file, say "data.aml" & then put your primitive details there. Below is an example of describing a single red colored rectangle centered at 0,0 with a width & height of 100 pixels.

```data.aml```
```
<root>
	<figure>
		<rect width="100" height="100" fillcolor="#ff0000" id="myrect" x="0" y="0"></rect>
	</figure>
</root>
```

That's it. Now you import it into your project using:

```Main.cpp```
```
int main()
{
	Artemis::Parser parser;
	std::string data;

	std::fstream file("./data.aml", std::ios::in | std::ios::binary);
	file.seekg(0, std::ios::end);
	size_t length = file.tellg();
	file.seekg(0, std::ios::beg);

	data.resize(length);

	// Read the data
	file.read(&data[0], length);
	file.close();

	// Set the syntax
	parser.setSyntax(data);

	// Check if the parsing succeeded
	if (parser.Parse() == false)
	{
		std::cout << "Failed to parse data!";
		return 1;
	}

	// Grab the primitives
	Artemis::Tag primitives = parser.getPrimitives();

	// Draw them with your renderer
	Renderer *renderer = new Renderer();

	// Fictional Game Loop
	while(Game::Get()->Loop())
	{
		renderer->Draw(primitives);
	}

	// Free resources
	delete renderer;

	return 0;
}
```

That's it. 

## Tags
I will update this section soon. Currently working on some additional attributes for some tags which I feel are really necessary. Plus, I am lazy ;)