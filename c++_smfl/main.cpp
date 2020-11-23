#include <SFML/Graphics.hpp>
#include <SFML/Graphics.h>
#include <iostream>


using namespace sf;

int MAX_X = 1920;
int MAX_Y = 1080;

std::map < int, std:: basic_string < char > > fonts_dictionary =  { //FONTS DICTIONARY WITH KEY AMD PATH
        { 1,"..\\fonts\\arial.ttf"   },
        { 2,"..\\fonts\\comic.ttf"   },
        { 3,"..\\fonts\\Inkfree.ttf" },
        { 4,"..\\fonts\\ariblk.ttf"  }
};

std::map < int, int  > font_size_dictionary = {
        { 1, 25  },
        { 2, 30  },
        { 3,45   },
        { 4, 60  },
        { 5, 70  }
};


void resizeImage(const sf::Image& originalImage, sf::Image& resizedImage)
{
    const sf::Vector2u originalImageSize{ originalImage.getSize() };
    const sf::Vector2u resizedImageSize{ resizedImage.getSize() };

    
    for (unsigned int y{ 0u }; y < resizedImageSize.y; ++y)
    {
        for (unsigned int x{ 0u }; x < resizedImageSize.x; ++x)
        {
            unsigned int origX{ static_cast<unsigned int>(static_cast<double>(x) / resizedImageSize.x * originalImageSize.x) };
            unsigned int origY{ static_cast<unsigned int>(static_cast<double>(y) / resizedImageSize.y * originalImageSize.y) };
            resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
        }
    }
}



sf:: Image loadImagePath ( std::basic_string< char > path, sf::Image image ) {

    if ( !image.loadFromFile( path ) ){
        puts("Error loading the image, please verify the path and try again");
        exit(-1);
    }else{

        Vector2<unsigned int> img_size = image.getSize();

        if ( img_size.x < 600 and img_size.y < 600  ){
            puts("Image dimensions are to small, please select a bigger one");
            exit(-1);

        }else if ( img_size.x > MAX_X and img_size.y > MAX_Y ) {

            puts("Resizing...");
            sf::Image aux;
            aux.loadFromFile("..\\resize_images\\1980_1080.png"); //Loading auxiliar image
            resizeImage( image, aux ); //Resizing method
           // aux.saveToFile("..\\processed\\resized.png"); //Se puede dejar en memoria, plantear en quitarlo
            return aux;


        }else {
            return image;
        }

    }
}


sf:: Font loadFont ( int font_number ){

    if ( font_number < 1 or font_number > 4 ){
        puts("Incorrect font number");
        exit(-1);
    }else {

        sf::Font font;

        if ( !font.loadFromFile ( fonts_dictionary[ font_number ] )) {
            puts( "Something went wrong opening the font, verify the fonts dictionary" );
            exit( -1 );
        }

        return font; //Returning the font

    }

}

int fontSize ( int font_size_number ) {

    if ( font_size_number < 1 or font_size_number > 5 ){
        puts("Font size out of index, please verify the dictionary");
        exit(-1);
    }

    return font_size_dictionary[ font_size_number ];

}



void saveImage ( sf::Image image, sf::Text text_one, std::basic_string< char > file_name  ){

    sf::Texture image_texture;
    sf::RenderTexture render;
    sf::Sprite sprite;
    Vector2< unsigned int > image_size = image.getSize(); //Getting the size from the image to create render

    image_texture.loadFromImage( image );
    sprite.setTexture( image_texture ); //Setting the texture to sprite
    render.create( image_size.x, image_size.y );
    text_one.setPosition( image_size.x / 3, 0 );

    render.draw( sprite );
    render.draw( text_one );
    render.display();

    auto renderTexture = render.getTexture();
    auto toSaveImage   = renderTexture.copyToImage();

    toSaveImage.saveToFile("..\\processed\\" + file_name + ".png"); //Concatenate the filename
    puts("Image Saved sucessfully");

}


void textSettings( sf::Image image,std::basic_string < char > text1 , int font_number , int font_size_number , std::basic_string<char> filename ,std::basic_string < char > text2 = ""   ) { //OPTIONAL PARAMETER

    sf::Font font;
    sf::Text text_one;
    int font_size = fontSize( font_size_number ); //Return the font size from the method

    font = loadFont( font_number ); //Loading font from the method
    text_one.setFont( font );
    text_one.setCharacterSize( font_size );
    text_one.setString( text1 );

    if ( text2.length() != 0 ) {

        sf::Text text_two;
        text_two.setFont( font );
        text_two.setCharacterSize( font_size );
        text_two.setString( text2 );

    }

    saveImage( image, text_one, filename );






}









int main() {

    std::basic_string< char > texto ;

    texto = "Hola";

    std::cout<< texto << std::endl;

    
   // sf::Image image;
    //image = loadImagePath("..\\process\\mejorada.jpg", image);
    //textSettings( image,"Programando ando!!!...", 3, 4, "fer" );



    //extSetting( "Ignacio", 2, "Alfaro" );

    //textSetting( "Jose" , "Optional text");

    /*

    sf::Image image;
    sf::Font font;
    sf:: Text text;
    sf:: Texture textura_imagen;
    sf::RenderTexture textura_render;
    sf:: Sprite sprite;



    image = loadImagePath("..\\process\\big.png", image); //Path y Clase
    textura_imagen.loadFromImage( image ); //TEXTURE CLASS


    sf::Text text1;
    //Cargar la letra...

    font.loadFromFile ( R"(C:\Windows\Fonts\georgia.ttf)" );
    text.setFont( font );
    text.setString("Soy un puto crack!!!!!");
    text.setCharacterSize(70);
    Vector2<unsigned int> img_size = image.getSize();
    text.setPosition( img_size.x / 3, 0  );

    text1.setFont( font );
    text1.setString( "Muy crack perrito" );
    text1.setCharacterSize( 70 );
    text1.setPosition( img_size.x / 3, img_size.y / 1.1  );


    //text.setOrigin( 900   , 600 );


    sprite.setTexture( textura_imagen );

    textura_render.create(img_size.x, img_size.y);
    textura_render.draw( sprite );
    textura_render.draw( text );
    textura_render.draw( text1 );

    textura_render.display();

    auto captured = textura_render.getTexture();
    auto toSave = captured.copyToImage();

    toSave.saveToFile("..\\process\\nachondoo.png");

     */

    return 0;
}
