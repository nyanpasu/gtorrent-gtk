#include <gtorrent/Platform.hpp>
#include "GtkMainWindow.hpp"
#include "Gtk.hpp"

/**
 * Sets up the main window.
 * Loads builder resources
 */
gt::GuiGtk::GuiGtk(int argc, char **argv)
{
	// TODO add argc and argv
	m_app = Gtk::Application::create(argc, argv);

	m_builder = Gtk::Builder::create();
	try {
		m_builder->add_from_resource("/org/gtk/gtorrent/dialog_association.ui");
		m_builder->add_from_resource("/org/gtk/gtorrent/dialog_rss.ui");
		m_builder->add_from_resource("/org/gtk/gtorrent/widget_box_rss.ui");
		m_builder->add_from_resource("/org/gtk/gtorrent/widget_box_torrent.ui");
		m_builder->add_from_resource("/org/gtk/gtorrent/widget_panel_torrent.ui");
		m_builder->add_from_resource("/org/gtk/gtorrent/window_main.ui");
	}
	catch (const Glib::FileError &ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return;
	}
	catch (const Glib::MarkupError &ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return;
	}
	catch (const Gtk::BuilderError &ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return;
	}
}

extern unsigned char style_css[];

/**
 * Activate main window
 * Load assets
 */
int gt::GuiGtk::run()
{
	GtkMainWindow *mainWindow = nullptr;
	try {
		m_builder->get_widget_derived("GtkMainWindow", mainWindow);
		mainWindow->set_icon(Gdk::Pixbuf::create_from_resource("/org/gtk/gtorrent/gtorrent.png"));

		auto css = Gtk::CssProvider::create();
		auto screen = Gdk::Screen::get_default();
		css->load_from_data(std::string((char *) style_css));
		Gtk::StyleContext::add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	}
	catch (const Glib::FileError &ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
	}
	catch (const Glib::MarkupError &ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	}
	catch (const Gtk::BuilderError &ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}

	m_app->run(*mainWindow);

	return 0;
}
