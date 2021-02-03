#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

#include "Pendulum.hpp"
#include "ColorPalettes.hpp"

#include <sstream>
#include <time.h>

using namespace ci;
using namespace ci::app;

class MyApp : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;

    static void prepareSettings( App::Settings *settings ) {
        settings->setWindowSize(1000, 1000);
        getArgs() = settings->getCommandLineArgs();
        settings->setTitle("Procedural Spirograph");
    }
    static std::vector<std::string>& getArgs() { static std::vector<std::string> args; return args; }

private:
    /**
     * Update pendulum information
     *
     * @param random The seed
     * @return Updated pendulum
     */
    Pendulum updatePendulum(Rand random);
    /**
     * Generate seed information to display on rendered image
     *
     * @param seed The text to be displayed
     */
    void genSeedText(std::string seed);

    std::vector<vec2> generateShape(int seed, int steps);

    int getRandomSeed();

    // Pendulum info
    std::vector<vec2> finishedShape;

    // App modifiers
    int seed;
    int renderQty;
    int imageSteps;

    //Colors
    bool useRandomColors;
    bool useOneColor;
    ColorA backgroundC;
    ColorA foregroundC;

    //Pendulum modifiers
    bool randomMovement;
    bool randomReset;

    // App runtime data
    int genCur = 0;

    // Display test
    gl::TextureRef seedTexture;
};

Pendulum MyApp::updatePendulum(Rand random) {
    vec2 origin = getWindowCenter();
    int maxSize = getWindowHeight()/2;

    int pendulum_size = random.nextInt(1, 4);

    float minSpeed = -10.0;
    float maxSpeed = 10.0;
    float minLen = 20.0;
    float maxLen = maxSize/pendulum_size;

    Pendulum pend;

    pend.init(origin, random.nextFloat(minSpeed, maxSpeed),
              random.nextFloat(minLen, maxLen));
    for (int i = 1; i < pendulum_size; i++) {
        pend.push_back(random.nextFloat(minSpeed, maxSpeed),
                       random.nextFloat(minLen, maxLen));
    }

    return pend;
}

void MyApp::genSeedText(std::string seed) {
    // Generate seed text
    std::string text = seed;
    Color textColor = Color(255, 255, 255);
    Font textFont = Font("Times New Roman", 24);
    vec2 textSize = vec2(150,100);

    TextBox tbox = TextBox().alignment(TextBox::LEFT).font(textFont).size(ivec2(textSize.x, TextBox::GROW)).text(text);
    tbox.setColor(textColor);
    tbox.setBackgroundColor(ColorA(0,0,0,0));
    ivec2 sz = tbox.measure();
    seedTexture = gl::Texture2d::create(tbox.render());
}

std::vector<vec2> MyApp::generateShape(int seed, int steps=50000) {
    Rand random(seed);
    Pendulum pend = this->updatePendulum(random);
    std::vector<vec2> shape;
    // First iter always causes trouble
    std::vector<std::vector<vec2>> points = pend.get_next();

    int randomProbability = 10000;
    int randomInt = random.nextInt(0, randomProbability);
    for (int s = 1; s < steps; s++) {

        if (randomMovement) {
            int move = random.nextInt(0, 10);
            if (move > 5) {
                int hor = random.nextFloat(-2, 2);
                int ver = random.nextFloat(-2, 2);
                pend.points[0].pos.x += hor;
                pend.points[0].pos.y += ver;
            }
        }

        if (randomReset) {
            int prob = random.nextInt(0, randomProbability);
            if (prob == randomInt) {
                s = 1;
                randomProbability *= 10;
                randomInt = random.nextInt(0, randomProbability);

                pend = this->updatePendulum(random);
                // Give info that its reset
                shape.push_back(vec2(-1, -1));
            }
        }

        points = pend.get_next();
        shape.push_back(points[points.size()-1][1]);
    }

    finishedShape = shape;
    return shape;
}

int MyApp::getRandomSeed() {
    cinder::Rand::randomize();
    Rand random(cinder::Rand::randInt());
    return random.nextInt();
}

void MyApp::setup() {

    imageSteps = 50000;
    seed = getRandomSeed();
    renderQty = 1;
    randomMovement = false;
    randomReset = true;

    useRandomColors = true;
    //useOneColor is for preventing change when changing styles
    useOneColor = false;
    //Preset colors
    backgroundC = ColorA(0.0f,0.0f,0.0f,1.0f);
    foregroundC = ColorA(1.0f,1.0f,1.0f,0.5f);

    for( auto arg = getArgs().begin(); arg != getArgs().end(); ++arg) {
        if (*arg == "-h") {
            std::cout << "--fullscreen\n"
                         "\tForce the application into fullscreen\n"
                         "--res x y\n"
                         "\tApplication resolution\n"
                         "--steps s\n"
                         "\tHow many steps per rendered image\n"
                         "--seed s\n"
                         "\tForce a specific seed\n"
                         "--renderQty q\n"
                         "\tHow many images to generate\n"
                         "--randomMovement\n"
                         "\tRandomize movement\n"
                         "--useOneColor\n"
                         "\tDisables color variation\n"
                         "[--background, --foreground] red green blue alpha\n"
                         "\tSets a color state\n" << std::endl;
            quit();
        }
        else if (*arg == "--fullscreen") {
            setFullScreen(true);
        }
        else if (*arg == "--res") {
            ++arg;
            int x = std::stoi(std::string(*arg));
            ++arg;
            int y = std::stoi(std::string(*arg));
            setWindowSize(x, y);
        }
        else if (*arg == "--steps") {
            ++arg;
            imageSteps = std::stoi(std::string(*arg));
        }
        else if (*arg == "--seed") {
            ++arg;
            renderQty = 1;
            seed = std::stoi(std::string(*arg));
        }
        else if (*arg == "--renderQty") {
            ++arg;
            renderQty = std::stoi(std::string(*arg));
        }
        else if (*arg == "--randomMovement") {
            randomMovement = true;
        }
        else if (*arg == "--useOneColor") {
            useOneColor = true;
        }
        else if (*arg == "--background") {
            ++arg;
            float r = std::stoi(std::string(*arg)) / 255;
            ++arg;
            float g = std::stoi(std::string(*arg)) / 255;
            ++arg;
            float b = std::stoi(std::string(*arg)) / 255;
            ++arg;
            float a = std::stoi(std::string(*arg)) / 255;
            backgroundC = ColorA(r, g, b, a);
            useRandomColors = false;
        }
        else if (*arg == "--foreground") {
            ++arg;
            float r = std::stoi(std::string(*arg)) / 255;
            ++arg;
            float g = std::stoi(std::string(*arg)) / 255;
            ++arg;
            float b = std::stoi(std::string(*arg)) / 255;
            ++arg;
            float a = std::stoi(std::string(*arg)) / 255;
            foregroundC = ColorA(r, g, b, a);
            useRandomColors = false;
        }
    }

}

void MyApp::update() {

    int duration = time(0);
    if (genCur != renderQty) {
        // Seed generation
        // First seed is always from the determined setup
        if (genCur != 0) {
            seed = getRandomSeed();
        }
        this->genSeedText(std::to_string(seed));
        this->generateShape(seed, imageSteps);
    }
    std::cout << "Took " << time(0) - duration << " seconds" << std::endl;
}

void MyApp::draw() {
    if (genCur != renderQty) {

        // Pick random palette
        Rand random(seed);
        ColorPalette colors = palettes[random.nextInt(0, palettes.size())];

        if (useRandomColors) {
            int backgroundPos = random.nextInt(0, colors.size()-1);
            backgroundC = ColorAT<float>::hex(colors[backgroundPos]);
            // remove to prevent the foreground from using that same color
            colors.erase(colors.begin() + backgroundPos);
            foregroundC = ColorAT<float>::hex(colors[random.nextInt(0, colors.size()-1)]);
            foregroundC.a = 0.5f;
        }

        // Setup colors
        gl::clear(backgroundC);
        gl::color(ColorA(1, 1, 1, 1));
        gl::draw(seedTexture);
        gl::color(foregroundC);

        // Draw shape
        for (int i = 1; i < finishedShape.size(); i++) {
            if (finishedShape[i].x == -1 && finishedShape[i].y == -1) {
                if(useRandomColors & !useOneColor) {
                    foregroundC = ColorAT<float>::hex(colors[random.nextInt(0, colors.size()-1)]);
                    foregroundC.a = 0.5f;
                    gl::color(foregroundC);
                    i += 2; //Skip the switch
                }
            } else {
                gl::drawLine(finishedShape[i-1], finishedShape[i]);
            }
        }

        genCur++;
        finishedShape.clear();
        auto t = getHomeDirectory() / "Pictures" / "ProceduralSpirograph" / (std::to_string(seed) + ".png");
        std::cout << "Saved in: " << t << std::endl;
        writeImage(t, copyWindowSurface());

        if (genCur == renderQty) {
            quit();
        }

    }
}

CINDER_APP(MyApp, RendererGl, &MyApp::prepareSettings);