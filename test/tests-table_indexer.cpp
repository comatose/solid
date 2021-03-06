#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid table_indexer", "[table_indexer]") {
  constexpr int numbers[] = {1, 2, 15, 5, 7};

  SECTION("table_indexer for numbers") {
    constexpr solid::table_indexer<int, 5> indexer(numbers);

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : numbers) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }

  SECTION("another table_indexer for numbers") {
    constexpr auto indexer = solid::make_table_indexer({1, 2, 15, 5, 7});

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : numbers) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }

  constexpr solid::static_string_view strings[] = {"table", "indexer", "for",
                                                   "strings"};

  SECTION("table_indexer for strings") {
    solid::table_indexer<solid::static_string_view, 5> indexer(strings);

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : strings) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }

  SECTION("table_indexer for strings") {
    constexpr auto indexer =
        solid::make_table_indexer<5, solid::static_string_view>(
            {"hash", "indexer", "for", "strings"});

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : strings) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }
}
