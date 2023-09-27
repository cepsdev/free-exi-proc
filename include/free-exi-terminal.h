#pragma once
/*
    free-exi-proc - an EXI (= "Efficient XML Interchange") processor
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

#include <stdexcept>
#include "exi-model-adapter.h"

namespace v2g_guru_exi{

    class Grammar::Terminal{
        private:
            bool wild_card_uri() const { return !qname.uri; }                
            bool wild_card_local_name() const {return !qname.local_name;}
            bool wild_card_local_name_only() const {return !qname.local_name && qname.uri;}                
            bool wild_card() const {return wild_card_uri() && wild_card_local_name(); }                
        public:
            using ev_type_t = uint16_t;
            ev_type_t ev_type{};
            static constexpr ev_type_t INVALID{0};
            static constexpr ev_type_t SD{1};
            static constexpr ev_type_t ED{SD+1};
            static constexpr ev_type_t SE{ED+1};
            static constexpr ev_type_t EE{SE+1};
            static constexpr ev_type_t AT{EE+1};
            static constexpr ev_type_t CH{AT+1};
            static constexpr ev_type_t NS{CH+1};
            static constexpr ev_type_t CM{NS+1};
            static constexpr ev_type_t PI{CM+1};
            static constexpr ev_type_t DT{PI+1};
            static constexpr ev_type_t ER{DT+1};
            static constexpr ev_type_t SC{ER+1};

            bool qualified{};

            struct qname_t{
                exi_comment(
                    witness_ref{
                        id(__1__2); 
                        lines(33 .. 37);
                    };
                ) 
                optional<string_t> uri;
                optional<string_t> local_name;
                optional<string_t> prefix;
            } qname;

            struct content_t{
                optional<string_t> value;
                optional<string_t> inherited_uri;
                optional<string_t> inherited_name;
            } content;
            
            Terminal() = default;

            exi_model_interface(Terminal(grammar_elem_t rep_arg);)
            exi_model_interface(grammar_elem_t get_rep() const {return rep;})
            bool valid() const { return rep != nullptr;}
            string as_str() const;
            string name() const;
            void set_name(string);
            optional<content_t> get_content() const;
        private:
            exi_model_interface(grammar_elem_t rep{};)

    };
}
