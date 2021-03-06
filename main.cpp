// Note: Checkout: Allegro GUI and MasKing

#include "main.h"

// Note: Follow on here -- https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace%3A-Graphics

int main(int argc, char** argv)
{
    InitAllegro::allegro();
    InitAllegro::fontAddon();
    InitAllegro::ttfAddon();
    InitAllegro::resourcePath();
    InitAllegro::keyboard();

    auto* resolution = new Resolution(false);
    resolution->configure();

    ALLEGRO_DISPLAY* display = InitAllegro::display(resolution->getWidth(), resolution->getHeight());
    ALLEGRO_EVENT_QUEUE* queue = InitAllegro::eventQueue();
    ALLEGRO_TIMER* timer = InitAllegro::timer(1.0/30.0);

    InitConstants::colour();

    bool redraw = true;
    bool done = false;

    auto* background = new Image("background-one.jpg");

    auto imageCollection = new ImageCollection();

    imageCollection->add(background);

    Colour* panelFill = gColour->midBlue->clone(0.86);
    auto* menu = new Panel(120, 120, 400, 300, *panelFill, *gColour->dustyBlack, 3);

    menu->add(new Panel(10, 10, 50, 50, *gColour->dustyBlack));
    menu->add(new Panel(70, 10, 50, 50, *gColour->dustyBlack));

    auto* text = new FontStyle(
            (float) 1920-100,
            (float) 80,
            "LibreCaslonText-Regular.ttf",
            100,
            *gColour->white,
            ALLEGRO_ALIGN_RIGHT
    );

    auto* textTwo = new FontStyle(
            60,
            15,
            "LibreCaslonText-Bold.ttf",
            21,
            *gColour->white,
            ALLEGRO_ALIGN_CENTRE
    );

    auto* textBox = new TextBox(*textTwo, 600, 300, 240, 80, *gColour->midBlue);
    textBox->setText("Text Box");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (true) {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            background->draw(0, 0);
            text->write("DRONE SQUADRON");
            menu->draw();
            textBox->draw();
            al_flip_display();

            redraw = false;
        }
    }

    delete imageCollection;
    delete menu;
    delete text;
    delete textTwo;
    delete textBox;
    delete resolution;
    delete panelFill;
    delete gColour;
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

    return 0;
}
