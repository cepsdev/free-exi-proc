/*
    v2g-guru-exi - an EXI (= "Efficient XML Interchange") processor
    Copyright (C) 2023 Tomas Prerovsky <cepsdev@hotmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

namespace v2g_guru_exi{
    using namespace ceps::ast;
    using namespace std;

    class Processor{
        EventStream event_stream;
        stack<Grammar> grammars;
        map<string,Grammar> global_grammars;
        map<string,Grammar> generic_grammars;
        bool debug_output = false;
        bool debug_output_emit_eventcode = true;        
        bool match(Grammar::Terminal);
        //Well, yes we use runtime polymorphism refraining from type parametrization in this case (sometimes i surprise myself). 
        Emitter* emitter{};
        Grammar::Terminal last_match;
        
        StringTable uris{1};
        StringTable global_values;

        using string_table_id_t = string;
        map<string_table_id_t,StringTable> local_names;
        map< pair<string_table_id_t,string_table_id_t>, StringTable> local_values;
      
        public:
            struct parser_exception{std::string msg;};
            Processor();
            void set_start_grammar(Grammar g);
            void set_event_stream(EventStream ev_stream);
            void encode();
            void parse(Grammar g);
            bool parse(Grammar g, Grammar::Production prod);
            void insert(GenericGrammar);
            void emit_eventcode(Grammar& g, Grammar::Production prod);
            void set_emitter(Emitter* an_emitter) {emitter = an_emitter;}
            Grammar::Terminal get_last_match() const;
    };
}
 