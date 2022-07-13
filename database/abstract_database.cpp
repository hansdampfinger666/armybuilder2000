#include "abstract_database.h"
#include "text.h"

u64
AbstractDatabase::add(const string& name)
{
  // TODO this should be possible, maybe with some kind of type erasure
}

string
AbstractDatabase::get_name(const u64 id)
{
  auto result = vec::vkkv(id, id_, txt_id_, texts_->id_, texts_->txt_);
  if (result)
    return result.value();
  else
    return "";
}

vector<string>
AbstractDatabase::get_names()
{
  return texts_->get_names(txt_id_);
}

vector<string>
AbstractDatabase::get_names(const vector<u64>& ids)
{
  vector<u64> txt_ids(ids.size(), 0);

  for (u64 i = 0; auto id : ids) {
    auto index = vec::index(id_, id);
    if (!index)
      continue;
    txt_ids[i] = txt_id_[index.value()];
    i++;
  }
  return texts_->get_names(txt_ids);
}

std::optional<u64>
AbstractDatabase::get_id(const string& name)
{
  return vec::vkkv(name, texts_->txt_, texts_->id_, txt_id_, id_);
}

u64
Texts::add(const string& txt)
{
  auto index = vec::index(txt_, txt);
  if (index)
    return id_[index.value()];

  curr_id_++;
  id_.emplace_back(curr_id_);
  txt_.emplace_back(txt);
  frag_ = vec::calc_frag(id_);
  return curr_id_;
}

u64
Texts::add(const u64 id, const string& txt)
{
  auto index = vec::index(id_, id);
  if (!index)
    return add(txt);

  txt_[index.value()] = txt;
  return id_[index.value()];
}

bool
Texts::del(const u64 id, Texts& trashbin)
{
  auto index = vec::index(id_, id);
  if (!index || lng_ != trashbin.lng_)
    return false;

  trashbin.id_.emplace_back(id_[index.value()]);
  trashbin.txt_.emplace_back(txt_[index.value()]);
  id_[index.value()] = 0;
  frag_ = vec::calc_frag(id_);
  return true;
}

std::optional<Texts::Text>
Texts::get(const u64 id)
{
  auto index = vec::index(id_, id);
  if (!index)
    return {};
  return Text{ id_[index.value()], txt_[index.value()], lng_ };
}

std::optional<u64>
Texts::get_id(const string& txt)
{
  auto index = vec::index(txt_, txt);
  if (!index)
    return {};

  return index.value();
}

vector<u64>
Texts::get_ids(const vector<size_t>& indexes)
{
  return vec::get_values(id_, indexes);
}

vector<string>
Texts::get_names_by_index(const vector<size_t>& indexes)
{
  return vec::get_values(txt_, indexes);
}

vector<string>
Texts::get_names(const vector<u64>& ids)
{
  vector<string> txts(ids.size(), { "" });

  for (i32 i = 0; auto id : ids) {
    auto idx = vec::index(id_, id);
    if (idx)
      txts[i] = txt_[idx.value()];
    i++;
  }
  if (txts.size() == 0)
    return {};
  return txts;
}

vector<size_t>
Texts::get_indexes(const TextsViewFilter filter)
{
  switch (filter) {
    case TextsViewFilter::NONE:
      return vec::index_all(id_);
      break;
    case TextsViewFilter::NOT_INITIAL:
      return vec::index_where_not_initial(id_);
      break;
    default:
      break;
  }
}