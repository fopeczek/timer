//// Do not remove the include
//
//
//template<typename char_t>
//void ButtonTyper<char_t>::Update(){
//	m_timer.update();
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::Init(const char_t* alphabet, uint8_t alphabet_size, uint8_t text_length, uint8_t default_letter_id, char_t empty_letter, uint32_t blink_tm_off, uint32_t blink_tm_on){
//	m_alphabet = alphabet;
//	m_alphabet_size = alphabet_size;
//	m_text_size = text_length;
//	m_default_letter = default_letter_id;
//	m_blink_off = blink_tm_off;
//	m_blink_on = blink_tm_on;
//	m_empty_letter = empty_letter;
//	on_blink_off();
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::on_blink_on() {
//	m_timer.set_timer(m_blink_on, [&](){this->on_blink_off();}, 0);
//	m_draw_letter_at_callback(*this, m_alphabet[m_current_string[m_cur_pos]], m_cur_pos);
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::on_blink_off() {
//	m_timer.set_timer(m_blink_off, [&](){this->on_blink_on();}, 0);
//	m_draw_letter_at_callback(*this, m_empty_letter, m_cur_pos);
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::LeftArrowPressed(){
//
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::RightArrowPressed(){
//
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::UpArrowPressed(){
//
//}
//
//template<typename char_t>
//void ButtonTyper<char_t>::DownArrowPressed(){
//
//}
//
