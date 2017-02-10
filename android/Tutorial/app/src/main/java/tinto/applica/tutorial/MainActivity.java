package tinto.applica.tutorial;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {

    @Override
    protected String[] getLibraries() {
        return new String[] {
                "SDL2",
                "SDL2_image",
                "SDL2_mixer",
                // "SDL2_net",
                "SDL2_ttf",
                "main"
        };
    }
}
