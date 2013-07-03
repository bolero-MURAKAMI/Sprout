# Sprout C++ Library

*C++11 constexpr based Containers, Algorithms, Random numbers, Parsing, Ray tracing, Synthesizer, and others.*  
このライブラリは、C++11 の constexpr に対応したコンテナ、アルゴリズム、乱数、構文解析、レイトレーシング、シンセサイザー、その他の機能を提供する。  



## ドキュメント *(Document)*

Sprout C++ Library Wiki: http://www.boleros.x0.com/doc/sproutwiki/  



## インストール *(Install)*

ディレクトリ `/path/to/sprout` にパスを通す。  
このライブラリはヘッダオンリーで使える。  
*(Through the path to the directory. `/path/to/sprout`*  
*This library can be used in the header only.)*  



## コンテンツ *(Contents)*

### コンテナとデータ構造 *(Containers and Data structures)*
* `sprout/array.hpp` - std::array 互換の固定長コンテナ  
* `sprout/string.hpp` - 固定長バッファの文字列クラス  
* `sprout/tuple.hpp` - std::tuple 互換のタプル  
* `sprout/optional.hpp` - 無効値の表現  
* `sprout/variant.hpp` - バリアント  
* `sprout/bitset.hpp` - std::bitset 互換のビットセット  

### アルゴリズム *(Algorithms)*
* `sprout/algorithm.hpp` - STL 互換のアルゴリズム  
* `sprout/algorithm/string.hpp` - 文字列用アルゴリズム  
* `sprout/numeric.hpp` - STL 互換の数値シーケンスアルゴリズム  
* `sprout/range/algorithm.hpp` - Rangeベースのアルゴリズム  
* `sprout/range/numeric.hpp` - Rangeベースの数値シーケンスアルゴリズム  
* `sprout/range/adaptor.hpp` - Rangeアダプタ  
* `sprout/numeric/dft.hpp` - 離散フーリエ変換  
* `sprout/range/numeric/dft.hpp` - Rangeベースの離散フーリエ変換  

### コンテナサポート *(Container supports)*
* `sprout/sub_array.hpp` - コンテナから一部の範囲を切り出す部分コンテナ  
* `sprout/pit.hpp` - 処理結果のコンテナを返す関数に与えるダミーコンテナ  
* `sprout/operation.hpp` - コンテナを変更する操作  
* `sprout/container.hpp` - コンテナ特性を定義するトレイトと関数  

### 関数オブジェクト *(Function Objects)*
* `sprout/functional.hpp` - STL 互換の関数オブジェクトとハッシュ関数  

### イテレータ *(Iterators)*
* `sprout/iterator.hpp` - STL 互換のイテレータと、いくつかの定義済みイテレータ  

### 数学 *(Mathematics)*
* `sprout/math/functions.hpp` - 数学関数  
* `sprout/random.hpp` - 乱数  
* `sprout/complex.hpp` - 複素数  
* `sprout/rational.hpp` - 有理数  

### テンプレートメタプログラミング *(Template Metaprogramming)*
* `sprout/index_tuple.hpp` - IndexTuple イディオム  
* `sprout/type_traits.hpp` - 型特性  
* `sprout/type.hpp` - 型リスト  

### プリプロセッサメタプログラミング *(Preprocessor Metaprogramming)*
* `sprout/preprocessor.hpp` - プリプロセッサメタプログラミングツール  

### ドメイン固有 *(Domain specific)*
* `sprout/uuid.hpp` - UUID  
* `sprout/checksum.hpp` - チェックサム (SHA-1, MD5, etc)  

### 構文解析 *(Parsing)*
* `sprout/weed.hpp` - Boost.Spirit.Qi ライクなコンパイル時パーサコンビネータ  

### レイトレーシング *(Ray tracing)*
* `sprout/darkroom.hpp` - コンパイル時レイトレーサ  

### シンセサイザー *(Synthesizer)*
* `sprout/compost.hpp` - コンパイル時シンセサイザー  

### その他 *(Miscellaneous)*
* `sprout/utility.hpp` - 標準ヘッダ utility 互換の機能と、雑多なユーティリティ  
* `sprout/bit/operation.hpp` - ビット操作  

### C互換 *(C-compatible)*
* `sprout/cstdlib.hpp` - 標準ヘッダ cstdlib 互換の機能  
* `sprout/cstring.hpp` - 標準ヘッダ cstring 互換の機能  
* `sprout/cwchar.hpp` - 標準ヘッダ cwchar 互換の機能  
* `sprout/cctype.hpp` - 標準ヘッダ cctype 互換の機能  
* `sprout/cinttypes.hpp` - 標準ヘッダ cinttypes 互換の機能  



## ユーザコンフィグ *(User configuration)*

これらのマクロを定義するのは、このライブラリのどのヘッダをインクルードするよりも以前でなければならない。  
*(To define these macros must be earlier than any of this library to include the header.)*  


### 言語機能のワークアラウンド *(Workaround for incomplete language features)*

* constexpr  
`#define SPROUT_CONFIG_DISABLE_CONSTEXPR`  
このマクロが定義されているとき、関数は constexpr 指定されない。  
コンパイラが constexpr に対応していない場合、これを定義すべき。  
通常、これはコンパイラに応じて自動的に定義される。  
*(When this macro is defined, the functions are not specified constexpr.*  
*If the compiler does not support constexpr, should define it.*  
*Usually, it defined automatically depending to the compiler.)*  

* noexcept  
`#define SPROUT_CONFIG_DISABLE_NOEXCEPT`  
このマクロが定義されているとき、関数は noexcept 修飾されない。  
コンパイラが noexcept に対応していない場合、これを定義すべき。  
通常、これはコンパイラに応じて自動的に定義される。  
*(When this macro is defined, the functions are not qualified noexcept.*  
*If the compiler does not support noexcept, should define it.*  
*Usually, it defined automatically depending to the compiler.)*  

* Template aliases  
`#define SPROUT_CONFIG_DISABLE_TEMPLATE_ALIASES`  
このマクロが定義されているとき、Template aliases によるエイリアスは定義されない。  
コンパイラが Template aliases に対応していない場合、これを定義すべき。  
通常、これはコンパイラに応じて自動的に定義される。  
*(When this macro is defined, the aliases are not defined by the Template aliases.*  
*If the compiler does not support Template aliases, should define it.*  
*Usually, it defined automatically depending to the compiler.)*  

* Delegating constructors  
`#define SPROUT_CONFIG_DISABLE_DELEGATING_CONSTRUCTORS`  
このマクロが定義されているとき、Delegating constructors による実装は行われない。  
コンパイラが Delegating constructors に対応していない場合、これを定義すべき。  
通常、これはコンパイラに応じて自動的に定義される。  
*(When this macro is defined, the implementation is not done by Delegating constructors.*  
*If the compiler does not support Delegating constructors, should define it.*  
*Usually, it defined automatically depending to the compiler.)*  

* 自動無効化の抑制 *(Not automatically disable)*  
`#define SPROUT_CONFIG_DISABLE_AUTO_CONFIG`  
このマクロが定義されているとき、自動的な言語機能の無効化は行われない。  
*(When this macro is defined, not automatically disable language features.)*  


### 実装の切り替え *(Switching implementation)*

* CEL - ConstExpr Library  
`#define SPROUT_CONFIG_USE_SSCRISK_CEL`  
このマクロが定義されているとき、実装の詳細として CEL - ConstExpr Library を使用する。  
*(When this macro is defined, you use the CEL - ConstExpr Library as an implementation detail.)*  
See: https://github.com/sscrisk/CEL---ConstExpr-Library  

* ビルトイン数学関数 *(Built-in mathematical functions)*  
`#define SPROUT_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION`  
このマクロが定義されているとき、数学関数の実装にビルトイン関数を使用しない。  
*(When this macro is defined, does not use the built-in function to the implementation of mathematical functions.)*  

* ビルトインビット処理 *(Built-in bit operations)*  
`#define SPROUT_CONFIG_DISABLE_BUILTIN_BIT_OPERATION`  
このマクロが定義されているとき、ビット処理の実装にビルトイン関数を使用しない。  
*(When this macro is defined, does not use the built-in function to the implementation of bit operations.)*  

* 一時オブジェクト渡しのサポート *(Support passing a temporary object)*  
`#define SPROUT_CONFIG_DISABLE_SUPPORT_TEMPORARY_CONTAINER_ITERATION`  
このマクロが定義されているとき、アルゴリズムへのコンテナの一時オブジェクト渡しをサポートしない。  
*(When this macro is defined, does not support passing a temporary object of the container to the algorithm.)*  

* 効率的な配列走査のサポート *(Support efficient iteration of the array)*  
`#define SPROUT_CONFIG_DISABLE_SUPPORT_EFFICIENT_ARRAY_ITERATION`  
このマクロが定義されているとき、効率的な配列走査をサポートしない。  
*(When this macro is defined, does not support efficient iteration of the array.)*  



## サポートするコンパイラ *(Supported Compilers)*

Linux:  
* GCC, C++11 mode: 4.7.0, 4.7.1, 4.7.2, 4.7.3, 4.8.0, 4.8.1  
* Clang, C++11 mode: 3.2, 3.3  



## 作者 *(Author)*

Bolero MURAKAMI  

Website: http://www.boleros.x0.com/  
Twitter: https://twitter.com/bolero_murakami  
Facebook: http://www.facebook.com/genya.murakami  
Blog: http://d.hatena.ne.jp/boleros/  
Github: https://github.com/bolero-MURAKAMI  
SlideShare: http://www.slideshare.net/GenyaMurakami  
Mail: contact-lib@boleros.x0.com  



## 著作権等 *(Copyrights)*

このライブラリは Boost Software License の元で公開されています。  

Copyright (C) 2011-2012 Bolero MURAKAMI.  
Distributed under the Boost Software License, Version 1.0.  
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)  
