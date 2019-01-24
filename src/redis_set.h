#pragma once

#include "redis_metadata.h"

class RedisSet : public RedisDBSubKeyScanner {
public:
  explicit RedisSet(Engine::Storage *storage, std::string ns) : RedisDBSubKeyScanner(storage, std::move(ns)) {}
  rocksdb::Status Add(Slice key, std::vector<Slice> members, int *ret);
  rocksdb::Status Remove(Slice key, std::vector<Slice> members, int *ret);
  rocksdb::Status Card(Slice key, int *ret);
  rocksdb::Status Members(Slice key, std::vector<std::string> *members);
  rocksdb::Status IsMember(Slice key, Slice member, int *ret);
  rocksdb::Status Take(Slice key, std::vector<std::string> *members, int count, bool pop);
  rocksdb::Status Move(Slice src, Slice dst, Slice member, int *ret);
  uint64_t Scan(Slice key,
                const std::string &cursor,
                const uint64_t &limit,
                const std::string &member_prefix,
                std::vector<std::string> *members);
private:
  rocksdb::Status GetMetadata(Slice key, SetMetadata *metadata);
};